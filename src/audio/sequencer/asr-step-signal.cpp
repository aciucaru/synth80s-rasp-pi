#include "asr-step-signal.h"

namespace synth80s
{
    AsrStepSignal::AsrStepSignal(AudioContext* audioContext)
                    : AudioProcessor(audioContext),
                        stepSignal(audioContext)
    {
        const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
        this->outputBlock = new float[BLOCK_SIZE]();

        this->setSamplesPerStep();
    }

    float* AsrStepSignal::getProcessedOutput() { return this->outputBlock; }

    void AsrStepSignal::process(float* inputBlock)
    {
        this->stepSignal.process();
        const float* stepSignalOutput = this->stepSignal.getProcessedOutput();

        const int BPM = this->stepSignal.getBPM();
        const int STEP_COUNT = this->stepSignal.getStepCount();
        const int SAMPLES_PER_STETP = this->stepSignal.getSamplesPerStep();

        const float ATTACK_RAMP = 1.0f / (this->attackSamples - 1.0f);
        const float RELEASE_RAMP = 1.0f / (this->releaseSamples - 1.0f);

        // generate the values of the block buffer and fill that buffer
        // the buffer is internal to this class, inherited from 'AudioNode' class */
        const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();

        // we compute first iteration separately
        this->previousStep = stepSignalOutput[0];
        this->currentStep = stepSignalOutput[0];

        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            // attack phase
            if (this->computedSamples < this->attackSamples)
            {
                this->outputBlock[i] = this->previousSample + ATTACK_RAMP;
                this->previousSample = this->outputBlock[i];
            }
            // sustain phase
            else if (this->attackSamples <= this->computedSamples &&
                    this->computedSamples < this->attackSamples + this->sustainSamples)
            {
                this->outputBlock[i] = 1.0f;
                this->previousSample = 1.0f;
            }
            // release phase
            else if (this->attackSamples + this->sustainSamples <= this->computedSamples &&
                    this->computedSamples < this->attackSamples + this->sustainSamples + this->releaseSamples)
            {
                this->outputBlock[i] = this->previousSample - RELEASE_RAMP;
                this->previousSample = this->outputBlock[i];
            }

            this->currentStep = stepSignalOutput[i];

            this->computedSamples++;

            // if we have reached a step change
            if (this->currentStep != this->previousStep)
            {
                // then reset the number of computed samples
                this->computedSamples = 0;
            }

            this->previousStep = this->currentStep;
        }
    }

    void AsrStepSignal::setBPM(float bpm)
    {
        this->stepSignal.setBPM(bpm);
        this->setSamplesPerStep();
    }

    int AsrStepSignal::getBPM() { return this->stepSignal.getBPM(); }

    void AsrStepSignal::setStepCount(int stepCount)
    {
        this->stepSignal.setStepCount(stepCount);
    }

    int AsrStepSignal::getStepCount() { return this->stepSignal.getStepCount(); }

    void AsrStepSignal::setSamplesPerStep()
    {
        const int SAMPLES_PER_STEP = this->stepSignal.getSamplesPerStep();

        this->attackSamples = static_cast<int>(lround(this->attackDuration * SAMPLES_PER_STEP));
        this->releaseSamples = static_cast<int>(lround(this->releaseDuration * SAMPLES_PER_STEP));
        this->sustainSamples = SAMPLES_PER_STEP - this->attackSamples - this->releaseSamples;
    }
}
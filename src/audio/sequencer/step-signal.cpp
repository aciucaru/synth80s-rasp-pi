#include "step-signal.h"

namespace synth80s
{
    StepSignal::StepSignal(AudioContext* audioContext)
                    : AudioProcessor(audioContext)
    {
        const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
        this->outputBlock = new float[BLOCK_SIZE]();

        this->setSamplesPerStep();
    }

    float* StepSignal::getProcessedOutput() { return this->outputBlock; }

    void StepSignal::process(float* inputBlock)
    {
        // generate the values of the block buffer and fill that buffer
        // the buffer is internal to this class, inherited from 'AudioNode' class */
        const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
        for (int i = 0; i < BLOCK_SIZE; i++)
        {
            /* Compute the actual sine value, the sin() uses 'phase' as main argument,
            ** which initial starts from 0.0f */
            this->outputBlock[i] = this->currentStepValue;

            // Increment the number of computed (generated) samples
            this->computedSamples++;

            // std::cout << "SAMPLES_PER_STEP: " << this->samplesPerStep << ", computedSamples: " << this->computedSamples << ", STEP_COUNT: " << this->stepCount << ", stepValue: " << this->currentStepValue << std::endl;

            /* Check if we have reached a complete step.
            ** We use >= because the bpm can change in real time, and thus, so can 'samplesPerStep'. */
            if (this->computedSamples >= this->samplesPerStep)
            {
                // Reset the number of computed samples
                this->computedSamples = 0;

                /* Increment the value of the step, so the next step will have
                ** a defferent signal value that the previos step */
                this->currentStepValue++;

                /* But also check if the value for the next step has been incremented
                ** too much and reset it if so.
                ** We use >= instead of == because the 'stepCount' can change in real time. */
                if (this->currentStepValue >= (this->stepCount + 1))
                    this->currentStepValue = 1; // reset step value
            }
        }
    }

    void StepSignal::setBPM(float bpm)
    {
        if (2.0 <= bpm && bpm <= 300.0)
        {
            this->bpm = bpm;
            this->setSamplesPerStep();
        }
    }

    int StepSignal::getBPM() { return this->bpm; }

    void StepSignal::setStepCount(int stepCount)
    {
        if (1 <= stepCount && stepCount <= 8)
            this->stepCount = stepCount;
    }

    int StepSignal::getStepCount() { return this->stepCount; }

    int StepSignal::getSamplesPerStep() { return this->samplesPerStep; }

    void StepSignal::setSamplesPerStep()
    {
        // compute the length (in samples) of one step
        this->samplesPerStep = static_cast<int>(lround(60.0f * this->audioContext->getSampleRate() / this->bpm));
    }
}

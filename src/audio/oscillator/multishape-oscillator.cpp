#include "multishape-oscillator.h"

namespace synth80s
{
  MultishapeOscillator::MultishapeOscillator(AudioContext* audioContext)
  : AudioProcessor(audioContext),
	triangleOscillator(audioContext),
    sawtoothOscillator(audioContext),
    squareOscillator(audioContext)
  {
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    this->outputBlock = new float[BLOCK_SIZE]();
  }

  float* MultishapeOscillator::getProcessedOutput() { return this->outputBlock; }

  void MultishapeOscillator::process(float* inputBlock)
  {
    // make all the oscillator generate their output
    this->triangleOscillator.process();
    this->sawtoothOscillator.process();
    this->squareOscillator.process();

    // store the outputs in a block (array)
    this->triangleOscBlock = this->triangleOscillator.getProcessedOutput();
    this->sawtoothOscBlock = this->sawtoothOscillator.getProcessedOutput();
    this->squareOscBlock = this->squareOscillator.getProcessedOutput();

    // combine the oscillators output and store it into the output block of this class
    const int BLOCK_SIZE = this->audioContext->getFramesPerBuffer();
    float weightsSum = 0.0f;
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
	  weightsSum = this->triangleOscWeight + this->sawtoothOscWeight + this->squareOscWeight;
	  if (weightsSum > 0.001)
		  this->outputBlock[i] = this->gain * ( this->triangleOscBlock[i] * this->triangleOscWeight + 
												this->sawtoothOscBlock[i] * this->sawtoothOscWeight +
												this->squareOscBlock[i] * this->squareOscWeight ) / weightsSum;
	  else
		  this->outputBlock[i] = 0.0f;
    }
  }

  void MultishapeOscillator::setTriangleWeight(float weight)
  {
    if (0.0f <= weight && weight <= 1.0f)
      this->triangleOscWeight = weight;
  }
  
  void MultishapeOscillator::setSawtoothWeight(float weight)
  {
    if (0.0f <= weight && weight <= 1.0f)
      this->sawtoothOscWeight = weight;
  }
  
  void MultishapeOscillator::setSquareWeight(float weight)
  {
    if (0.0f <= weight && weight <= 1.0f)
      this->squareOscWeight = weight;
  }

  void MultishapeOscillator::setFrequency(float frequency)
  {
	this->triangleOscillator.setFrequency(frequency);
    this->sawtoothOscillator.setFrequency(frequency);
    this->squareOscillator.setFrequency(frequency);
  }

  // sets the gain
  void MultishapeOscillator::setGain(float gain)
  {
    this->gain = gain;
  }
}

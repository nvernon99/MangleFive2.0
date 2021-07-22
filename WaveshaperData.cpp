/*
  ==============================================================================

    WaveshaperData.cpp
    Created: 1 Apr 2021 4:12:28pm
    Author:  nolan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveshaperData.h"

//==============================================================================
void WaveshaperData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{

    waveshaper.functionToUse = [](float x)
    {
        return std::tanh(x);
    };

    in_gain.reset();
    waveshaper.reset();
    out_gain.reset();

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;

    in_gain.prepare(spec);
    waveshaper.prepare(spec);
    out_gain.prepare(spec);

    isPrepared = true;
}

void WaveshaperData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> block{ buffer };
    in_gain.process(juce::dsp::ProcessContextReplacing<float> { block });
    waveshaper.process(juce::dsp::ProcessContextReplacing<float> { block });
    out_gain.process(juce::dsp::ProcessContextReplacing<float> { block });
}

void WaveshaperData::updateParameters(const int waveType, const float gainIn, const float gainOut)
{
    
    switch (waveType)
    {
    case 0:
        waveshaper.functionToUse = [](float x)
        {
            return std::tanh(x);
        };
        break;

    case 1:
        waveshaper.functionToUse = [](float x)
        {
            return juce::jlimit(float(-0.5), float(0.5), x);
        };
        break;

    case 2:
        waveshaper.functionToUse = [](float x)
        {
            return x / juce::MathConstants<float>::pi;
        };
        break;
    }
    
    in_gain.setGainDecibels(gainIn);
    out_gain.setGainDecibels(gainOut);
}

void WaveshaperData::reset()
{
    in_gain.reset();
    waveshaper.reset();
    out_gain.reset();
}
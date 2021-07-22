/*
  ==============================================================================

    WaveshaperData.h
    Created: 1 Apr 2021 4:12:28pm
    Author:  nolan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveshaperData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateParameters(const int waveType, const float gainIn, const float gainOut);
    void reset();

private:
    juce::dsp::Gain<float> in_gain;
    juce::dsp::WaveShaper<float> waveshaper;
    juce::dsp::Gain<float> out_gain;
    bool isPrepared{ false };
};

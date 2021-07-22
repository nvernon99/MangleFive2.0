/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FilterComponent.h"
#include "WaveshaperComponent.h"
#include "VernonOscilloscope.h"
#include "TitleComponent.h"

//==============================================================================
/**
*/


class MangleFiveAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MangleFiveAudioProcessorEditor (MangleFiveAudioProcessor&);
    ~MangleFiveAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //AudioOscilloscope oscillo;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MangleFiveAudioProcessor& audioProcessor;
    FilterComponent filterA;
    FilterComponent filterB;
    WaveshaperComponent waveA;
    WaveshaperComponent waveB;
    WaveshaperComponent waveC;
    TitleComponent title;
    //AudioOscilloscope &oscillo = audioProcessor.procOsc;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MangleFiveAudioProcessorEditor)
};

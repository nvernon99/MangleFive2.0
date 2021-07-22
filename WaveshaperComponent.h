/*
  ==============================================================================

    WaveshaperComponent.h
    Created: 1 Apr 2021 3:55:57pm
    Author:  nolan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "KnobLAF.h"
#include "VernonKnobLAF.h"

//==============================================================================
/*
*/
class WaveshaperComponent : public juce::Component
{
public:
    WaveshaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~WaveshaperComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector{ "MODE" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Slider gainInSlider;
    juce::Slider gainOutSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> gainInAttachment;
    std::unique_ptr<Attachment> gainOutAttachment;

    juce::Label filterSelectorLabel{ "Wave Type", "MODE" };
    juce::Label filterFreqLabel{ "Gain In", "IN" };
    juce::Label filterResLabel{ "Gain Out", "OUT" };

    VernonKnobLAF knobLAF2;

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveshaperComponent)
};
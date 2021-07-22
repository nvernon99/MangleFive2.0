/*
  ==============================================================================

    FilterComponent.h
    Created: 1 Apr 2021 3:55:17pm
    Author:  nolan

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>
#include "VernonKnobLAF.h"

//==============================================================================
/*
*/
class FilterComponent : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
   

private:
    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> filterFreqAttachment;
    std::unique_ptr<Attachment> filterResAttachment;

    juce::Label filterSelectorLabel{"Filter Type", "MODE" };
    juce::Label filterFreqLabel{ "Filter Freq", "CUTOFF"};
    juce::Label filterResLabel{"FilterRes", "RESO" };

    VernonKnobLAF knobLAF;

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};
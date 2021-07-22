/*
  ==============================================================================

    WaveshaperComponent.cpp
    Created: 1 Apr 2021 3:55:57pm
    Author:  nolan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveshaperComponent.h"
#include "VernonLook.h"

//==============================================================================
WaveshaperComponent::WaveshaperComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId)
{
    juce::StringArray choices{ "Softclip", "Hardclip", "Saw" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);

    /*
    filterSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont(15.0f);
    filterSelectorLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(filterSelectorLabel);
    */

    setSliderWithLabel(gainInSlider, filterFreqLabel, apvts, filterFreqId, gainInAttachment);
    setSliderWithLabel(gainOutSlider, filterResLabel, apvts, filterResId, gainOutAttachment);
}

WaveshaperComponent::~WaveshaperComponent()
{
}

void WaveshaperComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(POH(2));
    auto labelSpace = bounds.removeFromTop(POH(6));

    g.setColour(juce::Colours::orangered);
    //g.fillRoundedRectangle(getLocalBounds().toFloat(), POW(4));
    auto drawBckgrd = VernonImages::orange();
    g.addTransform(juce::AffineTransform::scale(3.0f, 3.0f, bounds.getWidth()/2.0f, bounds.getHeight()/2.0f));
    drawBckgrd->drawWithin(g, getLocalBounds().toFloat(), juce::RectanglePlacement::centred, 1.0f);
    g.addTransform(juce::AffineTransform::scale(3.0f, 3.0f, bounds.getWidth()/2.0f, bounds.getHeight()/2.0f).inverted());
    g.resetToDefaultState();
    g.setColour(juce::Colours::black);
    g.setFont(VernonFonts::satan(bounds.POH(10)));
    g.drawText("SHAPER", labelSpace.withX(5), juce::Justification::centred);
    g.drawRoundedRectangle(bounds.withTrimmedTop(POH(2)).toFloat(), 5.0f, 2.0f);
}

void WaveshaperComponent::resized()
{
    const auto startY = POW(47);
    const auto sliderWidth = POW(80);
    const auto sliderHeight = POW(73);
    const auto labelYOffset = POW(19);
    const auto labelHeight = POW(19);
    const auto yDiff = POH(45);

    filterTypeSelector.setBounds(POW(10), startY - POH(5), getLocalBounds().POW(80), POH(10));
    filterSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    gainInSlider.setBounds(POW(10), startY + POH(9), sliderWidth, sliderHeight);
    filterFreqLabel.setFont(VernonFonts::satan(POH(6)));
    filterFreqLabel.setBounds(gainInSlider.getX(), gainInSlider.getY() + sliderHeight, gainInSlider.getWidth(), labelHeight);

    gainOutSlider.setBounds(POW(10), startY + yDiff, sliderWidth, sliderHeight);
    filterResLabel.setFont(VernonFonts::satan(POH(6)));
    filterResLabel.setBounds(gainOutSlider.getX(), gainOutSlider.getY() + sliderHeight, gainOutSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void WaveshaperComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    slider.setLookAndFeel(&knobLAF2);
    //getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::black);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setFont(VernonFonts::satan(18.0f));
    label.setJustificationType(juce::Justification::centredBottom);
    addAndMakeVisible(label);
}
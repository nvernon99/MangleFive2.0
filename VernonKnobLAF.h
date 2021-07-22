/*
  ==============================================================================

    VernonKnobLAF.h
    Created: 16 Jul 2021 11:01:07am
    Author:  nolan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VernonLook.h"
#pragma once

class VernonKnobLAF : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        juce::Rectangle<int> sliderBounds;
        sliderBounds.setBounds(x, y, width, height);

        auto drawKnob = VernonImages::knob();
        g.addTransform(juce::AffineTransform::rotation(angle, centreX, centreY));
        drawKnob->drawWithin(g, sliderBounds.toFloat(), juce::RectanglePlacement::centred, 1.0f);
        
        //g.drawImageWithin(VernonImages::knob(), x, y, width, height, juce::RectanglePlacement::centred, false);
        //g.drawImageTransformed(juce::AffineTransform::rotation(angle).translated(centreX, centreY);
    }
};
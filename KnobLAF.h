/*
  ==============================================================================

    KnobLAF.h
    Created: 1 Jul 2021 3:57:33pm
    Author:  nolan

  ==============================================================================
*/
#include <JuceHeader.h>
#include "VernonLook.h"
#pragma once

class KnobLAF : public juce::LookAndFeel_V4
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
            auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

            // fill
            g.setColour(juce::Colours::darkgrey.withBrightness(0.1f));
            g.fillEllipse(rx, ry, rw, rw);

            // outline
            g.setColour(juce::Colours::black.withBrightness(0.1f));
            g.drawEllipse(rx, ry, rw, rw, 1.0f);

            juce::Path p;
            auto pointerLength = radius * 0.5f;
            auto pointerThickness = float(width)*0.05f;
            p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
            p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

            // pointer
            g.setColour(juce::Colours::silver);
            g.fillPath(p);
        }
};
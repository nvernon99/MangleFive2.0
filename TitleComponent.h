/*
  ==============================================================================

    TitleComponent.h
    Created: 19 Jul 2021 4:23:17pm
    Author:  nolan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VernonLook.h"

//==============================================================================
/*
*/
class TitleComponent  : public juce::Component
{
public:
    TitleComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~TitleComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.setColour(juce::Colours::silver.withAlpha(0.8f));
        //g.setFont(40.0f);
        g.setFont(VernonFonts::satan(getHeight()));
        g.drawSingleLineText("MANGLEFIVE", POW(50), POH(82), juce::Justification::centred);
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleComponent)
};

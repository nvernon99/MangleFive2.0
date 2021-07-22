/*
  ==============================================================================

    VernonLook.h
    Created: 29 Jun 2021 4:39:34pm
    Author:  nolan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "VernonOscilloscope.h"

#define POW(p) getWidth() * p * 1e-2f
#define POH(p) getHeight() * p * 1e-2f


//AudioOscilloscope myOsc = AudioOscilloscope();

class VernonFonts
{
public:

	static juce::Font satan(float height, float kerning = .1f)
	{
		return fonts().f_satan.withHeight(height).withExtraKerningFactor(kerning);
	}

private:

	VernonFonts() { }

	static VernonFonts& fonts()
	{
		static VernonFonts instance;
		return instance;
	}

protected:

	juce::Font f_satan{ juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::who_asks_satan_ttf,
															   BinaryData::who_asks_satan_ttfSize)) };
};

class VernonImages
{
public:
	static const juce::Drawable* knob() { return images().i_knob.get(); }
	static const juce::Drawable* red() { return images().i_red.get(); }
	static const juce::Drawable* orange() { return images().i_orange.get(); }
private:

	VernonImages() { }

	static VernonImages& images()
	{
		static VernonImages instance;
		return instance;
	}

	VernonImages(VernonImages const&);
	void operator= (VernonImages const&);

protected:
	std::unique_ptr<juce::Drawable> i_knob{ juce::Drawable::createFromImageData(BinaryData::knob1_svg,
																   BinaryData::knob1_svgSize) };
	std::unique_ptr<juce::Drawable> i_orange{ juce::Drawable::createFromImageData(BinaryData::orange_bckgrd1_svg,
																   BinaryData::orange_bckgrd1_svgSize) };
	std::unique_ptr<juce::Drawable> i_red{ juce::Drawable::createFromImageData(BinaryData::red_bckgrd1_svg,
																   BinaryData::red_bckgrd1_svgSize) };
};

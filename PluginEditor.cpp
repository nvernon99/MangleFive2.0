/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "VernonLook.h"

//==============================================================================
MangleFiveAudioProcessorEditor::MangleFiveAudioProcessorEditor (MangleFiveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), 
    filterA(audioProcessor.apvts, "FILTERTYPE_A", "FILTERFREQ_A", "FILTERRES_A"), 
    filterB(audioProcessor.apvts, "FILTERTYPE_B", "FILTERFREQ_B", "FILTERRES_B"),
    waveA(audioProcessor.apvts, "WAVETYPE_A", "WAVEIN_A", "WAVEOUT_A"),
    waveB(audioProcessor.apvts, "WAVETYPE_B", "WAVEIN_B", "WAVEOUT_B"),
    waveC(audioProcessor.apvts, "WAVETYPE_C", "WAVEIN_C", "WAVEOUT_C")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    //juce::ComponentBoundsConstrainer constrainer;
    //constrainer.setFixedAspectRatio(400 / 610);
    setResizable(true, true);
    setResizeLimits(305, 200, 1220, 800);
    auto constrain = getConstrainer();
    constrain->setFixedAspectRatio(double(610) / double(400));
    setConstrainer(constrain);
    setSize (610, 400);


    addAndMakeVisible(filterA);
    addAndMakeVisible(filterB);
    addAndMakeVisible(waveA);
    addAndMakeVisible(waveB);
    addAndMakeVisible(waveC);
    addAndMakeVisible(audioProcessor.procOsc);
    addAndMakeVisible(title);

    
}

MangleFiveAudioProcessorEditor::~MangleFiveAudioProcessorEditor()
{
}

//==============================================================================
void MangleFiveAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);
    g.setColour(juce::Colours::silver);
    //g.setFont(40.0f);
    g.setFont(VernonFonts::satan(POH(15)));
    //g.drawSingleLineText("MANGLEFIVE", POW(50), POH(12), juce::Justification::centred);
}

void MangleFiveAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const auto paddingX = POW(1);
    const auto paddingY = POH(10);
    const auto paddingY2 = POH(75);
    const auto yPos = POH(16);
    const auto xWidth = POW(19.5f);
    const auto yHeight = POH(80);
    waveA.setBounds(paddingX, yPos, xWidth, yHeight);
    filterA.setBounds(paddingX+xWidth, yPos, xWidth, yHeight);
    waveB.setBounds(paddingX+ (2*xWidth), yPos, xWidth, yHeight);
    filterB.setBounds(paddingX+ (3*xWidth), yPos, xWidth, yHeight);
    waveC.setBounds(paddingX+ (4*xWidth), yPos, xWidth, yHeight);
    audioProcessor.procOsc.setBounds(getLocalBounds().removeFromTop(POH(15)));
    title.setBounds(getLocalBounds().removeFromTop(POH(12)));
}

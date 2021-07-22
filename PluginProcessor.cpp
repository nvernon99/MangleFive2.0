/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "VernonOscilloscope.h"

//==============================================================================
MangleFiveAudioProcessor::MangleFiveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
        : AudioProcessor(BusesProperties()
        #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
                .withInput("Input", juce::AudioChannelSet::stereo(), true)
        #endif
                .withOutput("Output", juce::AudioChannelSet::stereo(), true)
        #endif
            ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    //procOsc = AudioOscilloscope();
}

MangleFiveAudioProcessor::~MangleFiveAudioProcessor()
{
}

//==============================================================================
const juce::String MangleFiveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MangleFiveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MangleFiveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MangleFiveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MangleFiveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MangleFiveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MangleFiveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MangleFiveAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MangleFiveAudioProcessor::getProgramName (int index)
{
    return {};
}

void MangleFiveAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MangleFiveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    filterA.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    filterB.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    waveA.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    waveB.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    waveC.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void MangleFiveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MangleFiveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MangleFiveAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
   
    
    auto& filterTypeA = *apvts.getRawParameterValue("FILTERTYPE_A");
    auto& cutoffA = *apvts.getRawParameterValue("FILTERFREQ_A");
    auto& resonanceA = *apvts.getRawParameterValue("FILTERRES_A");

    auto& filterTypeB = *apvts.getRawParameterValue("FILTERTYPE_B");
    auto& cutoffB = *apvts.getRawParameterValue("FILTERFREQ_B");
    auto& resonanceB = *apvts.getRawParameterValue("FILTERRES_B");
    
    auto& waveTypeA = *apvts.getRawParameterValue("WAVETYPE_A");
    auto& waveInA = *apvts.getRawParameterValue("WAVEIN_A");
    auto& waveOutA = *apvts.getRawParameterValue("WAVEOUT_A");

    auto& waveTypeB = *apvts.getRawParameterValue("WAVETYPE_B");
    auto& waveInB = *apvts.getRawParameterValue("WAVEIN_B");
    auto& waveOutB = *apvts.getRawParameterValue("WAVEOUT_B");

    auto& waveTypeC = *apvts.getRawParameterValue("WAVETYPE_C");
    auto& waveInC = *apvts.getRawParameterValue("WAVEIN_C");
    auto& waveOutC = *apvts.getRawParameterValue("WAVEOUT_C");
    

    filterA.updateParameters(filterTypeA, cutoffA, resonanceA);
    filterB.updateParameters(filterTypeB, cutoffB, resonanceB);
    
    waveA.updateParameters(waveTypeA, waveInA, waveOutA);
    waveB.updateParameters(waveTypeB, waveInB, waveOutB);
    waveC.updateParameters(waveTypeC, waveInC, waveOutC);


    waveA.process(buffer);
    filterA.process(buffer);
    waveB.process(buffer);
    filterB.process(buffer);
    waveC.process(buffer);

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        procOsc.processBlock(channelData, buffer.getNumSamples());
        //procOsc.clear();
        

        //
            // ..do something to the data...
    }
}

//==============================================================================
bool MangleFiveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MangleFiveAudioProcessor::createEditor()
{
    return new MangleFiveAudioProcessorEditor (*this);
}

//==============================================================================
void MangleFiveAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MangleFiveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin.
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MangleFiveAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout MangleFiveAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //Filter A
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE_A", "Filter Type A", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ_A", "Filter Freq A", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 1000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES_A", "Filter Resonance A", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));

    //Filter B
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE_B", "Filter Type B", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ_B", "Filter Freq B", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 1000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES_B", "Filter Resonance B", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));

    //Waveshaper A
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVETYPE_A", "Wave Type A", juce::StringArray{ "SOFT", "HARD", "SAW" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEIN_A", "Wave Gain In A", juce::NormalisableRange<float> { 1.0f, 30.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEOUT_A", "Wave Gain Out A", juce::NormalisableRange<float> { 1.0f, 20.0f, 0.1f }, 1.0f));

    //Waveshaper B
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVETYPE_B", "Wave Type B", juce::StringArray{ "SOFT", "HARD", "SAW" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEIN_B", "Wave Gain In B", juce::NormalisableRange<float> { 1.0f, 30.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEOUT_B", "Wave Gain Out B", juce::NormalisableRange<float> { 1.0f, 20.0f, 0.1f }, 1.0f));

    //Waveshaper C
    params.push_back(std::make_unique<juce::AudioParameterChoice>("WAVETYPE_C", "Wave Type C", juce::StringArray{ "SOFT", "HARD", "SAW" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEIN_C", "Wave Gain In C", juce::NormalisableRange<float> { 1.0f, 30.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("WAVEOUT_C", "Wave Gain Out C", juce::NormalisableRange<float> { 1.0f, 20.0f, 0.1f }, 1.0f));

    return { params.begin(), params.end() };
}



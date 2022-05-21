#pragma once

#include <JuceHeader.h>
#include <stdlib.h>
#include <string>
#include "CommandParser.h"
#include "SubDSP.h"

//==============================================================================

class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void setLowPassFilter(int channelNumber, int filterNumber, int freq);
    void setHighPassFilter(int channelNumber, int filterNumber, int freq);
    void removeFilter(int channeldNumber, int filterNumber);
    
private:
    //==============================================================================
    SubDSP dsp;
    CommandParser cmdp;
    juce::Image Logo;
    //int gainAssignments[6];
    juce::Label inputLabel;
    juce::Label inputText;
    juce::Label outputText;
    juce::TextButton enter;
    //juce::dsp::IIR::Filter<float> filterBank[16];
    //int filterAssignments[6][16];
    double currentSampleRate;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

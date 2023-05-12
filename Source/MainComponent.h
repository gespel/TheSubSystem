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

    void updateUI();
    double linearTodB(double input);

    juce::Label output1Label;
    juce::Label output1Text;
    juce::Label output2Label;
    juce::Label output2Text;
    juce::Label output3Label;
    juce::Label output3Text;
    juce::Label output4Label;
    juce::Label output4Text;
    juce::Label output5Label;
    juce::Label output5Text;
    juce::Label output6Label;
    juce::Label output6Text;
    juce::Label output7Label;
    juce::Label output7Text;
    juce::Label output8Label;
    juce::Label output8Text;    
    juce::Label output1MeterLabel;
    juce::Label output1MeterText;
    juce::Label output2MeterLabel;
    juce::Label output2MeterText;
    juce::Label output3MeterLabel;
    juce::Label output3MeterText;
    juce::Label output4MeterLabel;
    juce::Label output4MeterText;
    juce::Label output5MeterLabel;
    juce::Label output5MeterText;
    juce::Label output6MeterLabel;
    juce::Label output6MeterText;
    juce::Label output7MeterLabel;
    juce::Label output7MeterText;
    juce::Label output8MeterLabel;
    juce::Label output8MeterText;
    juce::Rectangle<int> output1Rect;

    juce::Image Logo;
    //int gainAssignments[6];
    juce::Label inputLabel;
    juce::Label inputText;
    juce::Label outputText;
    juce::TextButton enter;

    juce::Label infoLabel;

    juce::TextButton main;
    juce::TextButton routing;
    juce::TextButton filter;
    juce::TextButton commandline;
    juce::TextButton info;
    void clearMenu();
    
    //juce::dsp::IIR::Filter<float> filterBank[16];
    //int filterAssignments[6][16];
    double currentSampleRate;
    int uiUpdateStep = 0;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

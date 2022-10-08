/*
  ==============================================================================

    SubDSP.h
    Created: 6 May 2022 6:16:22pm
    Author:  Sten

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SubDSP {
public:
    SubDSP();
    void loadNextAudioBuffer(const juce::AudioSourceChannelInfo* bufferToFill, double sampleRate);
    void process();
    
    void setSteepLowPassFilter(int channelNumber, int filterNumber, int freq);
    void setSteepHighPassFilter(int channelNumber, int filterNumber, int freq);
    void setLowPassFilter(int channelNumber, int filterNumber, int freq);
    void setHighPassFilter(int channelNumber, int filterNumber, int freq);
    void removeFilter(int channelNumber, int filterNumber);
    void removeSteepFilter(int channelNumber, int filterNumber);
    void setGain(int channelNumber, int gain);
private:
    const juce::AudioSourceChannelInfo* currBuffer;
    juce::dsp::IIR::Filter<float> filterBank[16];
    juce::dsp::IIR::Filter<float> steepFilterBank[4][6];
    int filterAssignments[6][16]; //16 Filter for 6 Channels
    int steepFilterAssignments[6][4]; //4 Filter for 6 Channels
    int gainAssignments[6];
    double sampleRate;
    std::vector <std::vector<const float*>> routingtable;

    
};

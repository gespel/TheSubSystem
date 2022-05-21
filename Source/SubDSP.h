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
    
    void setLowPassFilter(int channelNumber, int filterNumber, int freq);
    void setHighPassFilter(int channelNumber, int filterNumber, int freq);
    void removeFilter(int channelNumber, int filterNumber);
    void setGain(int channelNumber, int gain);
private:
    const juce::AudioSourceChannelInfo* currBuffer;
    juce::dsp::IIR::Filter<float> filterBank[16];
    int filterAssignments[6][16];
    int gainAssignments[6];
    double sampleRate;

    
};

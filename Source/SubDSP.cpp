/*
  ==============================================================================

    SubDSP.cpp
    Created: 6 May 2022 6:16:22pm
    Author:  Sten

  ==============================================================================
*/

#include "SubDSP.h"

SubDSP::SubDSP() {
    
}

void SubDSP::loadNextAudioBuffer(const juce::AudioSourceChannelInfo* bufferToFill, double sampleRate) {
    this->currBuffer = bufferToFill;
    this->sampleRate = sampleRate;
}

void SubDSP::setLowPassFilter(int channelNumber, int filterNumber, int freq) {
    filterBank[filterNumber].coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq);
    filterAssignments[channelNumber][filterNumber] = 1;
}
void SubDSP::setHighPassFilter(int channelNumber, int filterNumber, int freq) {
    filterBank[filterNumber].coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, freq);
    filterAssignments[channelNumber][filterNumber] = 1;
}
void SubDSP::removeFilter(int channelNumber, int filterNumber) {
    filterAssignments[channelNumber][filterNumber] = 0;
}
void SubDSP::setGain(int channelNumber, int gain) {
    gainAssignments[channelNumber] = gain;
}

void SubDSP::process() {
    auto* inBufferL = currBuffer->buffer->getReadPointer(0, currBuffer->startSample);
    auto* inBufferR = currBuffer->buffer->getReadPointer(1, currBuffer->startSample);
    auto* outBufferL = currBuffer->buffer->getWritePointer(0, currBuffer->startSample);
    auto* outBufferR = currBuffer->buffer->getWritePointer(1, currBuffer->startSample);
    for(int sample = 0; sample < currBuffer->numSamples; sample++) {
        //======================= Input Routing =======================
        outBufferL[sample] = (inBufferL[sample] + inBufferR[sample])/2;
        outBufferR[sample] = (inBufferR[sample] + inBufferL[sample])/2;
        
        //======================= Filter Section =======================
        for(int filterNum = 0; filterNum < 16; filterNum++) {
            if(filterAssignments[0][filterNum] == 1) {
                outBufferL[sample] = filterBank[filterNum].processSample(outBufferL[sample]);
            }
        }
        for(int filterNum = 0; filterNum < 16; filterNum++) {
            if(filterAssignments[1][filterNum] == 1) {
                outBufferR[sample] = filterBank[filterNum].processSample(outBufferR[sample]);
            }
        }
        
        //======================= Gain Section =======================
        outBufferL[sample] *= (float)gainAssignments[0];
        outBufferR[sample] *= (float)gainAssignments[1];
    }
}

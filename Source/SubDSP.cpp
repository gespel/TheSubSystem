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
void SubDSP::setSteepLowPassFilter(int channelNumber, int filterNumber, int freq) {
    for(int i = 0; i < 6; i++) {
        steepFilterBank[filterNumber][i].coefficients = juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, freq);
    }
    steepFilterAssignments[channelNumber][filterNumber] = 1;
}
void SubDSP::setHighPassFilter(int channelNumber, int filterNumber, int freq) {
    filterBank[filterNumber].coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, freq);
    filterAssignments[channelNumber][filterNumber] = 1;
}
void SubDSP::setSteepHighPassFilter(int channelNumber, int filterNumber, int freq) {
    for(int i = 0; i < 6; i++) {
        steepFilterBank[filterNumber][i].coefficients = juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, freq);
    }
    steepFilterAssignments[channelNumber][filterNumber] = 1;
}
void SubDSP::removeFilter(int channelNumber, int filterNumber) {
    filterAssignments[channelNumber][filterNumber] = 0;
}
void SubDSP::removeSteepFilter(int channelNumber, int filterNumber) {
    steepFilterAssignments[channelNumber][filterNumber] = 0;
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
            if(filterAssignments[1][filterNum] == 1) {
                outBufferR[sample] = filterBank[filterNum].processSample(outBufferR[sample]);
            }
        }
        for(int filterNum = 0; filterNum < 4; filterNum++) {
            if(steepFilterAssignments[0][filterNum] == 1) {
                for(int i = 0; i < 6; i++) {
                    outBufferL[sample] = steepFilterBank[filterNum][i].processSample(outBufferL[sample]);
                }
            }
            if(steepFilterAssignments[1][filterNum] == 1) {
                for(int i = 0; i < 6; i++) {
                    outBufferR[sample] = steepFilterBank[filterNum][i].processSample(outBufferR[sample]);
                }
            }
        }
        
        //======================= Gain Section =======================
        outBufferL[sample] *= (float)gainAssignments[0];
        outBufferR[sample] *= (float)gainAssignments[1];
    }
}

/*
  ==============================================================================

    SubDSP.cpp
    Created: 6 May 2022 6:16:22pm
    Author:  Sten

  ==============================================================================
*/

#include "SubDSP.h"

SubDSP::SubDSP() {
    std::vector<const float*> left;
    std::vector<const float*> right;
    this->routingtable.push_back(left);
    this->routingtable.push_back(right);
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
void SubDSP::route(int inputChannel, int outputChannel) {
    this->routingtable[outputChannel].push_back(currBuffer->buffer->getReadPointer(inputChannel, currBuffer->startSample));
}

void SubDSP::process() {
    for (int sample = 0; sample < currBuffer->numSamples; sample++) {
        //======================= Input Routing =======================
        for (int i = 0; i < this->routingtable.size(); i++) { //iterates over outputchannels
            auto* outBuffer = currBuffer->buffer->getWritePointer(i, currBuffer->startSample);
            std::vector<const float*> x = routingtable[i];
            //for (int j = 0; j < x.size(); j++) {
            //    outBuffer[sample] += x[j][sample];
            //}
        }
        //======================= Filter Section =======================
        /*for (int filterNum = 0; filterNum < 16; filterNum++) {
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
        }*/

        //======================= Gain Section =======================
        //outBufferL[sample] *= (float)gainAssignments[0];
        //outBufferR[sample] *= (float)gainAssignments[1];
    }
}

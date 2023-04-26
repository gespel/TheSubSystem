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
void SubDSP::setGain(int channelNumber, double gain) {
    gainAssignments[channelNumber] = gain;
}
void SubDSP::setInputGain(int channelNumber, int gain) {
    inputGainAssignments[channelNumber] = gain;
}
void SubDSP::addInputChannel(int channelNumber, const float* channel) {
    while (channelNumber >= inputs.size()) {
        //inputs.push_back(const float* x);
    }
}
void SubDSP::route(int inputChannel, int outputChannel) {
    //this->routingtable[outputChannel].push_back(currBuffer->buffer->getReadPointer(inputChannel, currBuffer->startSample));
    /*while (outputChannel >= routingtable.size()) {
        routingtable.push_back(std::vector<const float*>());
    }*/
    routingtable[outputChannel].push_back(inputs[inputChannel]);
}

void SubDSP::process() {
    /*std::cout << this->routingtable[0].size() << " ";
    if(this->routingtable[0].size() > 0) {
        std::cout << this->routingtable[0][0][10] << std::endl;
    }*/
    for (int sample = 0; sample < currBuffer->numSamples; sample++) {
        //======================= Input Routing =======================
        for (int i = 0; i < this->routingtable.size(); i++) { //iterates over outputchannels
            auto* outBuffer = currBuffer->buffer->getWritePointer(i, currBuffer->startSample);
            std::vector<const float*> x = routingtable[i];
            for (int j = 0; j < x.size(); j++) {
                outBuffer[sample] += x[j][sample];
            }
            /*if(x.size() > 0) {
                outBuffer[sample] *= 1/x.size();
            }*/
        }
        //======================= Gain & Filter Section =======================
        for (int i = 0; i < this->routingtable.size(); i++) { //iterates over outputchannels
            auto* outBuffer = currBuffer->buffer->getWritePointer(i, currBuffer->startSample);
            
            for (int filterNum = 0; filterNum < 16; filterNum++) {
                if(filterAssignments[i][filterNum] == 1) {
                    outBuffer[sample] = filterBank[filterNum].processSample(outBuffer[sample]);
                }
            }
            for(int filterNum = 0; filterNum < 4; filterNum++) {
                if(steepFilterAssignments[i][filterNum] == 1) {
                    for(int i = 0; i < 6; i++) {
                        outBuffer[sample] = steepFilterBank[filterNum][i].processSample(outBuffer[sample]);
                    }
                }
            }
            
            outBuffer[sample] *= gainAssignments[i];
        }
    }
}

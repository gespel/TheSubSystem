/*
  ==============================================================================

    CommandParser.h
    Created: 4 May 2022 2:23:37pm
    Author:  Sten

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SubDSP.h"

class CommandParser {
public:
    CommandParser();
    void loadDSP(SubDSP* dsp);
    void parseCommandLine(juce::Label* inputText, juce::Label* outputText);
private:
    SubDSP* dsp;
};

/*
  ==============================================================================

    CommandParser.cpp
    Created: 4 May 2022 2:23:37pm
    Author:  Sten

  ==============================================================================
*/

#include "CommandParser.h"

CommandParser::CommandParser() {
    
}

void CommandParser::loadDSP(SubDSP *dsp) {
    this->dsp = dsp;
}
void CommandParser::parseCommandLine(juce::Label *inputText, juce::Label *outputText) {
    String input = inputText->getText();
    String inputArr[5];
    String word = "";
    String output;
    String outputHeader;
    int counter = 0;

    for(auto x : input) {
        if(x == ' ' || x == ';') {
            inputArr[counter] = word;
            word = "";
            counter++;
        }
        else {
            word = word + x;
        }
    }
    if(inputArr[0] == "setfilter") {
        //===============================================================================
        //setfilter [channelNumber] [filterNumber] [frequency] [filterType];
        //===============================================================================
        int channelNumber = atoi(inputArr[1].toStdString().c_str());
        int filterNumber = atoi(inputArr[2].toStdString().c_str());
        int freq = atoi(inputArr[3].toStdString().c_str());
        
        if(inputArr[4] == "lp") {
            dsp->setLowPassFilter(channelNumber, filterNumber, freq);
        }
        else if(inputArr[4] == "hp") {
            dsp->setHighPassFilter(channelNumber, filterNumber, freq);
        }
        else {
            output = "Unbekannter Filtertyp!";
            outputHeader = "Fehler";
            AlertWindow::showMessageBoxAsync(AlertWindow::NoIcon, outputHeader, output, "Ok", nullptr, nullptr);
            return;
        }
        
        output = "Filter ";
        output += filterNumber;
        output += " [";
        output += inputArr[4];
        output += " ";
        output += freq;
        output += " Hz] wurde auf Kanal ";
        output += channelNumber;
        output += " gesetzt!";
        outputHeader = "Erfolgreich!";	
    }
    else if (inputArr[0] == "route") {
        //===============================================================================
        //route [inputChannel] [outputChannel];
        //===============================================================================
        int in = atoi(inputArr[1].toStdString().c_str());
        int out = atoi(inputArr[2].toStdString().c_str());

        dsp->route(in, out);
        

        output = "Kanal ";
        output += in;
        output += " wurde auf Kanal ";
        output += out;
        output += " geroutet!";
        outputHeader = "Erfolgreich!";
    }
    else if(inputArr[0] == "setsteepfilter") {
        //===============================================================================
        //setsteepfilter [channelNumber] [filterNumber] [frequency] [filterType];
        //===============================================================================
        int channelNumber = atoi(inputArr[1].toStdString().c_str());
        int filterNumber = atoi(inputArr[2].toStdString().c_str());
        int freq = atoi(inputArr[3].toStdString().c_str());

        if(inputArr[4] == "lp") {
            dsp->setSteepLowPassFilter(channelNumber, filterNumber, freq);
        }
        else if(inputArr[4] == "hp") {
            dsp->setSteepHighPassFilter(channelNumber, filterNumber, freq);
        }
        else {
            output = "Unbekannter Filtertyp!";
            outputHeader = "Fehler";
            AlertWindow::showMessageBoxAsync(AlertWindow::NoIcon, outputHeader, output, "Ok", nullptr, nullptr);
            return;
        }

        output = "Filter ";
        output += filterNumber;
        output += " [";
        output += inputArr[4];
        output += " ";
        output += freq;
        output += " Hz] wurde auf Kanal ";
        output += channelNumber;
        output += " gesetzt!";
        outputHeader = "Erfolgreich!";
    }
    else if(inputArr[0] == "removefilter") {
        //===============================================================================
        //removefilter [channelNumber] [filterNumber];
        //===============================================================================
        int channelNumber = atoi(inputArr[1].toStdString().c_str());
        int filterNumber = atoi(inputArr[2].toStdString().c_str());
        
        dsp->removeFilter(channelNumber, filterNumber);
        //filterAssignments[channelNumber][filterNumber] = 0;
        
        output = "Filter ";
        output += filterNumber;
        output += " auf Kanal ";
        output += channelNumber;
        output += " wurde entfernt!";
    }
    else if(inputArr[0] == "removesteepfilter") {
        //===============================================================================
        //removesteepfilter [channelNumber] [filterNumber];
        //===============================================================================
        int channelNumber = atoi(inputArr[1].toStdString().c_str());
        int filterNumber = atoi(inputArr[2].toStdString().c_str());

        dsp->removeSteepFilter(channelNumber, filterNumber);

        output = "Filter ";
        output += filterNumber;
        output += " auf Kanal ";
        output += channelNumber;
        output += " wurde entfernt!";
        outputHeader = "Erfolgreich!";
    }
    else if(inputArr[0] == "setgain") {
        //===============================================================================
        //setgain [channelNumber] [gain];
        //===============================================================================
        int channelNumber = atoi(inputArr[1].toStdString().c_str());
        int gain = atoi(inputArr[2].toStdString().c_str());
        //gainAssignments[channelNumber] = gain;
        dsp->setGain(channelNumber, gain);
        
        output = "Gain Kanal ";
        output += channelNumber;
        output += " wurde auf ";
        output += gain;
        output += " gesetzt!";
        outputHeader = "Erfolgreich!";
    }
    else {
        output = "Unbekannter Befehl!";
        outputHeader = "Fehler!";
    }
    inputText->setText("", juce::dontSendNotification);
    outputText->setText(output, juce::dontSendNotification);
    AlertWindow::showMessageBoxAsync(AlertWindow::NoIcon, outputHeader, outputText->getText(), "Ok", nullptr, nullptr);
    //outputText.setText(inputArr[1], juce::dontSendNotification);
}

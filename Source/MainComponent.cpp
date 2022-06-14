#include "MainComponent.h"
#include <iostream>

//==============================================================================
MainComponent::MainComponent()
{
    setSize (400, 300);
    //Logo = ImageCache::getFromMemory(BinaryData::LOGO_PNG, BinaryData::LOGO_PNGSize);
    addAndMakeVisible(inputLabel);
    inputLabel.setText("Commandline:", juce::dontSendNotification);
    inputLabel.attachToComponent(&inputText, true);
    inputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    inputLabel.setJustificationType (juce::Justification::right);
    addAndMakeVisible(inputText);
    inputText.setEditable(true);
    inputText.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    addAndMakeVisible(outputText);
    outputText.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    addAndMakeVisible(enter);
    enter.setButtonText("Enter");
    enter.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    enter.onClick = [this] {
        cmdp.parseCommandLine(&inputText, &outputText);
    };

    
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    cmdp.loadDSP(&dsp);
    currentSampleRate = sampleRate;
    for(int i = 0; i < 6; i++) {
        dsp.setGain(i, 1);
    }
    juce::Logger::outputDebugString("\n=================================\nMade by Sten Heimbrodt [Audiotechnik Suboptimal]\n=================================\nEntwicklungsversion! Bugs sehr wahrscheinlich.\nAch ja, Nazis sind doof.\n=================================\n");
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels  = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    
    dsp.loadNextAudioBuffer(&bufferToFill, currentSampleRate);
    dsp.process();
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::orange);
    g.drawFittedText("Made by Audiotechnik Suboptimal", 5, 200, 200, 100, Justification::bottomLeft, 10);
    //g.drawImageAt(Logo, 0, 0);
}

void MainComponent::resized()
{
    inputText.setBounds(100, 10, getWidth() - 110, 20);
    outputText.setBounds(5, 40, getWidth() - 15, 20);
    enter.setBounds(90, 70, getWidth() - 190, 20);
}

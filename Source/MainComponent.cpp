#include "MainComponent.h"
#include <iostream>




//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 500);
    //Logo = ImageCache::getFromMemory(BinaryData::LOGO_PNG, BinaryData::LOGO_PNGSize);

    //MAIN MENU
    output1Label.setText("Output Gain Channel 1: ", juce::dontSendNotification);
    output1Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output1Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output2Label.setText("Output Gain Channel 2: ", juce::dontSendNotification);
    output2Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output2Text.setColour(juce::Label::textColourId, juce::Colours::black);
    

    output3Label.setText("Output Gain Channel 3: ", juce::dontSendNotification);
    output3Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output3Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output4Label.setText("Output Gain Channel 4: ", juce::dontSendNotification);
    output4Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output4Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output5Label.setText("Output Gain Channel 5: ", juce::dontSendNotification);
    output5Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output5Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output6Label.setText("Output Gain Channel 6: ", juce::dontSendNotification);
    output6Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output6Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output7Label.setText("Output Gain Channel 7: ", juce::dontSendNotification);
    output7Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output7Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output8Label.setText("Output Gain Channel 8: ", juce::dontSendNotification);
    output8Label.setColour(juce::Label::textColourId, juce::Colours::black);
    output8Text.setColour(juce::Label::textColourId, juce::Colours::black);

    output1MeterLabel.setText("Output Channel 1: ", juce::dontSendNotification);
    output1MeterLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    output1MeterText.setColour(juce::Label::textColourId, juce::Colours::black);
    //output1Rect.setColour(juce::Colours::black);
    addAndMakeVisible(output1Label);
    addAndMakeVisible(output1Text);
    addAndMakeVisible(output2Label);
    addAndMakeVisible(output2Text);
    addAndMakeVisible(output3Label);
    addAndMakeVisible(output3Text);
    addAndMakeVisible(output4Label);
    addAndMakeVisible(output4Text);
    addAndMakeVisible(output5Label);
    addAndMakeVisible(output5Text);
    addAndMakeVisible(output6Label);
    addAndMakeVisible(output6Text);
    addAndMakeVisible(output7Label);
    addAndMakeVisible(output7Text);
    addAndMakeVisible(output8Label);
    addAndMakeVisible(output8Text);
    addAndMakeVisible(output1MeterLabel);
    addAndMakeVisible(output1MeterText);
    //========================

    //COMMANDLINE MENU
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
    //========================

    //INFO MENU
    infoLabel.setText("Made by Audiotechnik Suboptimal\nDeveloper: Sten [Gespel] Heimbrodt\nTesting: FluctusMotus and Sten [Gespel] Heimbrodt", juce::dontSendNotification);
    infoLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    infoLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    addAndMakeVisible(infoLabel);
    //========================

    this->clearMenu();

    //MAIN MENU
    main.setButtonText("Main Menu");
    main.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    main.onClick = [this] {
        this->clearMenu();
        output1Label.setVisible(true);
        output1Text.setVisible(true);
        output2Label.setVisible(true);
        output2Text.setVisible(true);
        output3Label.setVisible(true);
        output3Text.setVisible(true);
        output4Label.setVisible(true);
        output4Text.setVisible(true);
        output5Label.setVisible(true);
        output5Text.setVisible(true);
        output6Label.setVisible(true);
        output6Text.setVisible(true);
        output7Label.setVisible(true);
        output7Text.setVisible(true);
        output8Label.setVisible(true);
        output8Text.setVisible(true);
        output1MeterLabel.setVisible(true);
        output1MeterText.setVisible(true);
    };
    addAndMakeVisible(main);

    routing.setButtonText("Routing");
    routing.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    routing.onClick = [this] {
        this->clearMenu();
    };
    addAndMakeVisible(routing);

    filter.setButtonText("Filter");
    filter.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    filter.onClick = [this] {
        this->clearMenu();
    };
    addAndMakeVisible(filter);

    commandline.setButtonText("Commandline");
    commandline.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    commandline.onClick = [this] {
        this->clearMenu();
        inputLabel.setVisible(true);
        inputText.setVisible(true);
        outputText.setVisible(true);
        enter.setVisible(true);
    };
    addAndMakeVisible(commandline);

    info.setButtonText("Info");
    info.setColour(juce::Label::backgroundColourId, juce::Colours::darkblue);
    info.onClick = [this] {
        this->clearMenu();
        infoLabel.setVisible(true);
    };
    addAndMakeVisible(info);
    //========================

    
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (4, 8);
    }
}

void MainComponent::updateUI() {
    output1Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[0])) + " dB", juce::dontSendNotification);
    output2Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[1])) + " dB", juce::dontSendNotification);
    output3Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[2])) + " dB", juce::dontSendNotification);
    output4Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[3])) + " dB", juce::dontSendNotification);
    output5Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[4])) + " dB", juce::dontSendNotification);
    output6Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[5])) + " dB", juce::dontSendNotification);
    output7Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[6])) + " dB", juce::dontSendNotification);
    output8Text.setText(std::to_string(this->linearTodB(dsp.gainAssignments[7])) + " dB", juce::dontSendNotification);
    output1MeterText.setText(std::to_string(this->linearTodB(std::abs(dsp.getFirstSamplesFromOutputChannels()[0]))) + " dB", juce::dontSendNotification);
}

double MainComponent::linearTodB(double input) {
    double db;

    if (input != 0.0f) {
        db = 20.0f * log10(input);
    }
    else {
        db = -144.0f;  // effectively minus infinity
    }
    return db;
}

void MainComponent::clearMenu() {
    inputLabel.setVisible(false);
    inputText.setVisible(false);
    outputText.setVisible(false);
    enter.setVisible(false);

    infoLabel.setVisible(false);

    output1Label.setVisible(false);
    output1Text.setVisible(false);
    output2Label.setVisible(false);
    output2Text.setVisible(false);
    output3Label.setVisible(false);
    output3Text.setVisible(false);
    output4Label.setVisible(false);
    output4Text.setVisible(false);
    output5Label.setVisible(false);
    output5Text.setVisible(false);
    output6Label.setVisible(false);
    output6Text.setVisible(false);
    output7Label.setVisible(false);
    output7Text.setVisible(false);
    output8Label.setVisible(false);
    output8Text.setVisible(false);
    output1MeterLabel.setVisible(false);
    output1MeterText.setVisible(false);
}
MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    dsp.routingtable.push_back(std::vector<const float*>());
    
    
    cmdp.loadDSP(&dsp);
    currentSampleRate = sampleRate;
    for(int i = 0; i < 8; i++) {
        dsp.setGain(i, 0.1);
    }
    juce::Logger::outputDebugString("\n=================================\nMade by Sten Heimbrodt [Audiotechnik Suboptimal]\n=================================\nEntwicklungsversion! Bugs sehr wahrscheinlich.\nAch ja, Nazis sind doof.\n=================================\n");
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeInputChannels  = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    dsp.inputs.clear();
    dsp.inputs.push_back(bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample));
    //dsp.inputs.push_back(bufferToFill.buffer->getReadPointer(1, bufferToFill.startSample));
    //dsp.inputs.push_back(bufferToFill.buffer->getReadPointer(2, bufferToFill.startSample));
    //dsp.inputs.push_back(bufferToFill.buffer->getReadPointer(3, bufferToFill.startSample));
    dsp.loadNextAudioBuffer(&bufferToFill, currentSampleRate);
    dsp.process();
    this->updateUI();
}

void MainComponent::releaseResources()
{

}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::orange);
    g.setColour(juce::Colours::green);
    g.drawRect(this->output1Rect, 2);
    //g.drawFittedText("Made by Audiotechnik Suboptimal", 5, 200, 200, 100, Justification::bottomLeft, 10);
    //g.drawImageAt(Logo, 0, 0);
}

void MainComponent::resized()
{
    double scaling = 5.75;

    output1Label.setBounds(10, 10, 180, 20);
    output1Text.setBounds(200, 10, 100, 20);
    output2Label.setBounds(10, 30, 180, 20);
    output2Text.setBounds(200, 30, 100, 20);
    output3Label.setBounds(10, 50, 180, 20);
    output3Text.setBounds(200, 50, 100, 20);
    output4Label.setBounds(10, 70, 180, 20);
    output4Text.setBounds(200, 70, 100, 20);
    output5Label.setBounds(10, 90, 180, 20);
    output5Text.setBounds(200, 90, 100, 20);
    output6Label.setBounds(10, 110, 180, 20);
    output6Text.setBounds(200, 110, 100, 20);
    output7Label.setBounds(10, 130, 180, 20);
    output7Text.setBounds(200, 130, 100, 20);
    output8Label.setBounds(10, 150, 180, 20);
    output8Text.setBounds(200, 150, 100, 20);
    output1MeterLabel.setBounds(10, 170, 180, 20);
    output1MeterText.setBounds(200, 170, 100, 20);
    output1Rect.setBounds(10, 220, 180*(std::abs(dsp.getFirstSamplesFromOutputChannels()[0])), 20);

    inputText.setBounds(100, 10, getWidth() - 110, 20);
    outputText.setBounds(5, 40, getWidth() - 15, 20);
    enter.setBounds(90, 70, getWidth() - 190, 20);

    infoLabel.setBounds(10, 10, getWidth()-20, 100);

    main.setBounds(10, getHeight()-25, getWidth()/scaling, 20);
    routing.setBounds(getWidth()/scaling+20, getHeight()-25, getWidth()/scaling, 20);
    filter.setBounds(getWidth()/scaling*2+30, getHeight()-25, getWidth()/scaling, 20);
    commandline.setBounds(getWidth()/scaling*3+40, getHeight()-25, getWidth()/scaling, 20);
    info.setBounds(getWidth()/scaling*4+50, getHeight()-25, getWidth()/scaling, 20);
}

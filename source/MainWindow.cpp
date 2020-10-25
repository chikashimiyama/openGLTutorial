#include "MainWindow.h"
#include "GLComponent.h"

MainWindow::MainWindow (juce::String name)
: DocumentWindow (name,
                  juce::Desktop::getInstance().getDefaultLookAndFeel()
                  .findColour (ResizableWindow::backgroundColourId),
                  DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new GLComponent(), true);
    setResizable (false, false);
    centreWithSize (800, 600);
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

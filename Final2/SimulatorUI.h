#ifndef SIMULATOR_UI_H
#define SIMULATOR_UI_H

#include "VoleMachine.h"

class SimulatorUI
{
    VoleMachine machine;

public:
    void start();
    void showMenu();
    void loadProgram();
    void overwriteValue();
    void runProgram();
    void displayState();
    bool askContinueOrExit();
};

#endif
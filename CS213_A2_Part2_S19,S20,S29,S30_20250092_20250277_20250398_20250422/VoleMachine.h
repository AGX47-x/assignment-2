#ifndef VOLE_MACHINE_H
#define VOLE_MACHINE_H

#include <string>
#include "Memory.h"
#include "RegisterFile.h"

class VoleMachine
{
    int pc = 0;
    std::string ir = "0000";
    bool halted = false;
    std::string screen = "";
    Memory memory;
    RegisterFile registers;

public:
    bool loadProgram(std::string filepath, int startAddress);
    bool step();
    void run();

    bool isHalted() { return halted; }
    void setHalted(bool h) { halted = h; }

    void writeScreen(int value, int address);

    int getPC() { return pc; }
    void setPC(int address) { pc = address; }
    std::string getIR() const { return ir; }
    Memory &getMemory() { return memory; }
    RegisterFile &getRegisters() { return registers; }
    std::string getScreen() const { return screen; }
};

#endif
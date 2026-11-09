#pragma once
#include "Instruction.h"

class LoadInstruction : public Instruction {
    int regIdx;
    int memAddress;
public:
    LoadInstruction(int r, int addr);
    void execute(VoleMachine &machine) override;
};

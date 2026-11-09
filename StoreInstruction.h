#pragma once
#include "Instruction.h"
class StoreInstruction : public Instruction {
    int regIdx;
    int memAddress;
public:
    StoreInstruction(int r, int addr);
    void execute(VoleMachine &machine) override;
};

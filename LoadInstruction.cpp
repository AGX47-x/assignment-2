#include "LoadInstruction.h"
#include "VoleMachine.h"
LoadInstruction::LoadInstruction(int r, int addr) : regIdx(r), memAddress(addr) {
    opcode = 1;
}
void LoadInstruction::execute(VoleMachine &machine) {
    int value = machine.getMemory().read(memAddress);
    machine.getRegisters().write(regIdx, value);
}

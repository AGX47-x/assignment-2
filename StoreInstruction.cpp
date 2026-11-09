#include "StoreInstruction.h"
#include "VoleMachine.h"
StoreInstruction::StoreInstruction(int r, int addr) : regIdx(r), memAddress(addr) {
    opcode = 2;
}
void StoreInstruction::execute(VoleMachine &machine) {
    int value = machine.getRegisters().read(regIdx);
    machine.getMemory().write(memAddress, value);
}

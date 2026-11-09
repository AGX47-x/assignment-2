#include "Instruction.h"
#include "VoleMachine.h"
#include <string>

// LoadInstruction
LoadInstruction::LoadInstruction(int r, int addr) : regIdx(r), memAddress(addr) { opcode = 1; }
void LoadInstruction::execute(VoleMachine &machine)
{
    int value = machine.getMemory().read(memAddress);
    machine.getRegisters().write(regIdx, value);
}

// LoadImmediateInstruction
LoadImmediateInstruction::LoadImmediateInstruction(int r, int val) : regIdx(r), value(val) { opcode = 2; }
void LoadImmediateInstruction::execute(VoleMachine &machine)
{
    machine.getRegisters().write(regIdx, value);
}

// StoreInstruction
StoreInstruction::StoreInstruction(int r, int addr) : regIdx(r), memAddress(addr) { opcode = 3; }
void StoreInstruction::execute(VoleMachine &machine)
{
    int value = machine.getRegisters().read(regIdx);
    machine.getMemory().write(memAddress, value);
    if (memAddress == 0xFF)
    {
        machine.writeScreen(value, 0xFF);
    }
}

// MoveInstruction
MoveInstruction::MoveInstruction(int target, int source) : targetRegister(target), sourceRegister(source) { opcode = 4; }
void MoveInstruction::execute(VoleMachine &machine)
{
    int val = machine.getRegisters().read(sourceRegister);
    machine.getRegisters().write(targetRegister, val);
}

// ArithmeticLogicInstruction
ArithmeticLogicInstruction::ArithmeticLogicInstruction(int opCode, int target, int s1, int s2)
    : targetRegister(target), sourceRegister1(s1), sourceRegister2(s2) { opcode = opCode; }

void ArithmeticLogicInstruction::execute(VoleMachine &machine)
{
    int val1 = machine.getRegisters().read(sourceRegister1);
    int val2 = machine.getRegisters().read(sourceRegister2);
    int result = 0;

    if (opcode == 5)
    {
        result = (val1 + val2) & 0xFF;
    }
    else if (opcode == 7)
    {
        result = val1 | val2;
    }
    else if (opcode == 8)
    {
        result = val1 & val2;
    }
    else if (opcode == 9)
    {
        result = val1 ^ val2;
    }
    machine.getRegisters().write(targetRegister, result);
}

// JumpInstruction
JumpInstruction::JumpInstruction(int r, int addr) : reg(r), targetAddress(addr) { opcode = 0x0B; }
void JumpInstruction::execute(VoleMachine &machine)
{
    int regVal = machine.getRegisters().read(reg);
    int R0Val = machine.getRegisters().read(0);
    if (regVal == R0Val)
    {
        machine.setPC(targetAddress);
    }
}

// HaltInstruction
HaltInstruction::HaltInstruction() { opcode = 0x0C; }
void HaltInstruction::execute(VoleMachine &machine)
{
    machine.setHalted(true);
}

// InstructionDecoder
bool InstructionDecoder::validate(std::string code)
{
    return code.length() == 4;
}

Instruction *InstructionDecoder::decode(std::string code)
{
    if (!validate(code))
        return nullptr;
    char opChar = code[0];
    int reg = std::stoi(code.substr(1, 1), nullptr, 16);
    int operand2 = std::stoi(code.substr(2, 2), nullptr, 16);
    int op = std::stoi(std::string(1, opChar), nullptr, 16);

    if (op == 1)
    {
        return new LoadInstruction(reg, operand2);
    }
    else if (op == 2)
    {
        return new LoadImmediateInstruction(reg, operand2);
    }
    else if (op == 3)
    {
        return new StoreInstruction(reg, operand2);
    }
    else if (op == 4)
    {
        int source = std::stoi(code.substr(3, 1), nullptr, 16);
        return new MoveInstruction(reg, source);
    }
    else if (op >= 5 && op <= 9)
    {
        int s1 = std::stoi(code.substr(2, 1), nullptr, 16);
        int s2 = std::stoi(code.substr(3, 1), nullptr, 16);
        return new ArithmeticLogicInstruction(op, reg, s1, s2);
    }
    else if (op == 0x0B)
    {
        return new JumpInstruction(reg, operand2);
    }
    else if (op == 0x0C)
    {
        return new HaltInstruction();
    }
    return nullptr;
}
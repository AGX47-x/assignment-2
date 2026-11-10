#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

class VoleMachine;
class Instruction
{
protected:
    int opcode;

public:
    virtual ~Instruction() {}
    virtual void execute(VoleMachine &machine) = 0;
};

class LoadInstruction : public Instruction
{
    int regIdx, memAddress;

public:
    LoadInstruction(int r, int addr);
    void execute(VoleMachine &machine) override;
};

class LoadImmediateInstruction : public Instruction
{
    int regIdx, value;

public:
    LoadImmediateInstruction(int r, int val);
    void execute(VoleMachine &machine) override;
};

class StoreInstruction : public Instruction
{
    int regIdx, memAddress;

public:
    StoreInstruction(int r, int addr);
    void execute(VoleMachine &machine) override;
};

class MoveInstruction : public Instruction
{
    int targetRegister, sourceRegister;

public:
    MoveInstruction(int target, int source);
    void execute(VoleMachine &machine) override;
};

class ArithmeticLogicInstruction : public Instruction
{
    int targetRegister, sourceRegister1, sourceRegister2;

public:
    ArithmeticLogicInstruction(int opCode, int target, int s1, int s2);
    void execute(VoleMachine &machine) override;
};

class JumpInstruction : public Instruction
{
    int reg, targetAddress;

public:
    JumpInstruction(int r, int addr);
    void execute(VoleMachine &machine) override;
};

class HaltInstruction : public Instruction
{
public:
    HaltInstruction();
    void execute(VoleMachine &machine) override;
};

class InstructionDecoder
{
public:
    bool validate(std::string code);
    Instruction *decode(std::string code);
};

#endif
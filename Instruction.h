#pragma once
class VoleMachine{};

class Instruction {
protected:
    int opcode;
    int r;
    int xy;
public:
    virtual ~Instruction() {}
    virtual void execute(VoleMachine &machine) = 0;
};

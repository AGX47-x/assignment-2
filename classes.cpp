#include <iostream>
using namespace std;

class Memory {
    int cells[256];
public:
    int read(int address) {}
    void write(int address, int value) {}
};

class RegisterFile {
    int registers[16];
public:
    int read(int id) {}
    void write(int id, int value) {}
};

class VoleMachine {
    int pc;
    string ir;
    bool halted;
    string screen;
public:
    bool loadProgram(string file, int startAddress) {} 
    bool step() {}  
    void run() {}  
    bool isHalted() {}  
    void writeScreen(int value) {}  
    int getPC() {}  
    void setPC(int address) {}  
    string getIR() {}  
    Memory getMemory() {}  
    RegisterFile getRegisters() {}  
    string getScreen() {}      
};

class SimulatorUI {
    VoleMachine machine;
public: 
    void start() {}
    void showMenu() {}
    void loadProgram() {}
    void overwriteValue() {}
    void runProgram() {}
    void displayState() {}
    bool askContinueOrExit() {}
};

class Instruction {
protected:
    int opcode;
    int r;
    int xy;
public:
    virtual void execute(VoleMachine& machine) = 0;
};

class InstructionDecoder {
public:
    bool validate(string code) {}
    Instruction* decode(string code) {}
};

class LoadInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
}; 

class StoreInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
};

class MoveInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
};

class ArithmeticLogicInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
};

class JumpInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
};

class HaltInstruction : public Instruction{
public:
    void execute(VoleMachine& machine) override {}
};


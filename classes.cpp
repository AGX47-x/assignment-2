#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class Memory
{
    int cells[256];

public:
    int read(int address) {}
    void write(int address, int value) {}
};

class RegisterFile
{
    int registers[16];

public:
    int read(int id) {}
    void write(int id, int value) {}
};

class VoleMachine
{
    int pc = 0;        
    string ir = "0000";
    bool halted = false;
    string screen = "";
    Memory memory;
    RegisterFile registers;

public:
    bool loadProgram(string filepath, int startAddress)
    {
        ifstream file(filepath);
        if (!file.is_open())
            return false;
        string line;
        int currentaddress = startAddress;
        while (getline(file, line))
        {
            if (line.empty() || line[0] == ';')
                continue;
            if (line.length() >= 4)
            {
                string hex1 = line.substr(0, 2);
                string hex2 = line.substr(2, 2);
                memory.write(currentaddress, stoi(hex1, nullptr, 16));
                memory.write(currentaddress + 1, stoi(hex2, nullptr, 16));
                currentaddress += 2;
            }
        }
        pc = startAddress;
        return true;
    }
    bool step()
    {
        if (halted)
            return false;
        int highbyte = memory.read(pc);
        int lowbyte = memory.read(pc + 1);
        stringstream ss;
        ss << hex << setw(2) << setfill('0') << highbyte 
           << hex << setw(2) << setfill('0') << lowbyte;
        ir = ss.str();
        InstructionDecoder decoder;
        Instruction* inst = decoder.decode(ir);
        if (inst != nullptr) {
            inst->execute(*this);
            delete inst;
        }
        pc += 2;
        return true;
    }
    void run()
    {
        while (!halted)
        {
            if (!step())
                break;
        }
    }
    bool isHalted() { return halted; }
    void setHalted(bool h) { 
        halted = h; 
    }
    void writeScreen(int value, int address)
    {
        if (address == 0xFF)
            screen += static_cast<char>(value);
    }
    int getPC() { return pc; }
    void setPC(int address) { pc = address; }
    string getIR() const { return ir; }
    Memory& getMemory() { return memory; }
    RegisterFile getRegisters() { return registers; }
    string getScreen() const { return screen; }
};

class SimulatorUI
{
    VoleMachine machine;

public:
    void start()
    {
        int choice;
        do
        {
            cin >> choice;
            switch (choice)
            {
            case 1:
                loadProgram();
                break;
            case 2:
                overwriteValue();
                break;
            case 3:
                runProgram();
                break;
            case 4:
                displayState();
                break;
            case 5:
                cout << "Exiting simulator\n";
                break;
            default:
                cout << "invalid choice! pls try again.\n";
            }
        } while (choice != 5 && askContinueOrExit());
    }
    void showMenu()
    {
        cout << "\n==============================\n"
             << "     VOLE MACHINE SIMULATOR   \n"
             << "==============================\n"
             << "1. Load Program from File\n"
             << "2. Overwrite Value (Memory/Register)\n"
             << "3. Run Program\n"
             << "4. Display Simulator State\n"
             << "5. Exit\n"
             << "Enter your choice: ";
    }
    void loadProgram()
    {
        string filename;
        int startadress;
        cout << "Enter name of the program ex(file.txt): ";
        cin >> filename;
        cout << "Enter start address in hex: ";
        cin >> startadress;
        if (machine.loadProgram(filename, startadress))
        {
            cout << "File loaded successfully.\n";
        }
        else
        {
            cout << "Could not open the file.\n";
        }
    }
    void overwriteValue()
    {
        int type;
        cout << "1. Overwrite Memory Cell\n2. Overwrite Register\nChoose option: ";
        cin >> type;
        if (type == 1)
        {
            int adr, val;
            cout << "Enter memory address(hex): ";
            cin >> adr;
            cout << "Enter value(hex): ";
            cin >> val;
            machine.getMemory().write(adr, val);
        }
        else if (type == 2)
        {
            int regid, val;
            cout << "Enter register index (0-15): ";
            cin >> regid;
            cout << "Enter value (hex): ";
            cin >> hex >> val;
            machine.getRegisters().write(regid, val);
        }
    }
    void runProgram()
    {
        cout << "Running program...\n";
        machine.run();
        cout << "Program execution completed or halted.\n";
    }
    void displayState()
    {
        cout << "\n--- SIMULATOR STATE ---\n";
        cout << "PC (Hex): 0x" << hex << machine.getPC() << "\n";
        cout << "IR (Hex): " << machine.getIR() << "\n";
        cout << "Halted:   " << (machine.isHalted() ? "Yes" : "No") << "\n";
        cout << "Screen Output: " << machine.getScreen() << "\n";

        cout << "\nRegisters:\n";
        for (int i = 0; i < 16; ++i)
        {
            cout << "R" << i << ": 0x" << setw(2) << setfill('0')
                 << hex << machine.getRegisters().read(i) << "  ";
            if ((i + 1) % 4 == 0)
                cout << "\n";
        }
        cout << "-----------------------\n";
    }
    bool askContinueOrExit()
    {
        char ch;
        cout << "\nWould you like to return to the main menu? (y/n): ";
        cin >> ch;
        return (ch == 'y' || ch == 'Y');
    }
};

class Instruction
{
protected:
    int opcode;
    int r;
    int xy;

public:
    virtual ~Instruction() {}
    virtual void execute(VoleMachine &machine) = 0;
};

class InstructionDecoder
{
public:
    bool validate(string code) {
        return code.length() == 4;
    }
    Instruction *decode(string code) {
        if (!validate(code)) return nullptr;
        char opChar = code[0];
        int reg = stoi(code.substr(1, 1), nullptr, 16);
        int address = stoi(code.substr(2, 2), nullptr, 16);
        int op = stoi(string(1, opChar), nullptr, 16);
        if (op == 1) {
            return new LoadInstruction(reg, address);
        }
        else if (op == 2) {
            return new StoreInstruction(reg, address);
        }
        else if (op == 4) {
            int target = reg;
            int source = stoi(code.substr(3, 1), nullptr, 16);
            return new MoveInstruction(target, source);
        }
        else if (op >= 5 && op <= 9) {
            int r = reg;
            int s1 = stoi(code.substr(2, 1), nullptr, 16);
            int s2 = stoi(code.substr(3, 1), nullptr, 16);
            return new ArithmeticLogicInstruction(op, r, s1, s2);
        }
        else if (op == 0x0B) {
            return new JumpInstruction(reg, address);
        }
        else if (op == 0x0C) {
            return new HaltInstruction();
        }

        return nullptr;
    }
};

class LoadInstruction : public Instruction
{
    int regIdx;
    int memAddress;
public:
    LoadInstruction(int r, int addr) : regIdx(r), memAddress(addr) {
        opcode = 1;
    void execute(VoleMachine &machine) override {
    int value = machine.getMemory().read(memAddress);
        machine.getRegisters().write(regIdx, value);
    }
};

class StoreInstruction : public Instruction
{
    int regIdx;
    int memAddress;
public:
    StoreInstruction(int r, int addr) : regIdx(r), memAddress(addr) {
        opcode = 2;
    void execute(VoleMachine &machine) override {
            int value = machine.getRegisters().read(regIdx);
        machine.getMemory().write(memAddress, value);
    }
};

class MoveInstruction : public Instruction
{
    int targetRegister;
    int sourceRegister;
public:
    MoveInstruction(int targetRegister, int sourceRegister) : targetRegister(targetRegister), sourceRegister(sourceRegister)  {
        opcode = 4;
    }
    void execute(VoleMachine &machine) override {
        int val = machine.getRegisters().read(sourceRegister);
        machine.getRegisters().write(targetRegister, val);
    }
};

class ArithmeticLogicInstruction : public Instruction
{
    int targetRegister;
    int sourceRegister1;
    int sourceRegister2;
public:
    ArithmeticLogicInstruction(int opCode, int targetRegister, int sourceRegister1, int sourceRegister2) :
    opcode(opCode), targetRegister(targetRegister), sourceRegister1(sourceRegister1), sourceRegister2(sourceRegister2) {}

    void execute(VoleMachine &machine) override {
        int val1 = machine.getRegisters().read(sourceRegister1);
        int val2 = machine.getRegisters().read(sourceRegister2);
        int result = 0;

        if(opcode == 5 || opcode == 6) {
            result = val1 + val2;
        } 
        else if (opcode == 7) {
            result = val1 | val2;
        } 
        else if (opcode == 8) {
            result = val1 & val2;
        } 
        else if (opcode == 9) {
            result = val1 ^ val2;
        }
        machine.getRegisters().write(targetRegister, result);
    }
};

class JumpInstruction : public Instruction
{
    int reg;
    int targetAddress;
public:
    JumpInstruction(int reg, int targetAddress) : reg(reg), targetAddress(targetAddress) {
        opcode = 0x0B;
    }
    void execute(VoleMachine &machine) override {
        int regVal = machine.getRegisters().read(reg);
        int R0Val = machine.getRegisters().read(0);

        if(regVal == R0Val) {
            machine.setPC(targetAddress);
        }
    }
};

class HaltInstruction : public Instruction
{
public:
    HaltInstruction() {
        opcode = 0x0C;
    }
    void execute(VoleMachine &machine) override {
        machine.setHalted(true);
    }
};

int main()
{
    SimulatorUI ui;
    ui.start();
    return 0;
}

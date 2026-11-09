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
    int pc;
    string ir;
    bool halted;
    string screen;
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
                currentaddress = 2;
            }
        }
        return true;
    }
    bool step()
    {
        if (halted)
            return false;
        int highbyte = memory.read(pc);
        int lowbyte = memory.read(pc + 1);
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
    void writeScreen(int value, int address)
    {
        if (address == 0xFF)
            screen += static_cast<char>(value);
    }
    int getPC() { return pc; }
    void setPC(int address) { pc = address; }
    string getIR() const { return ir; }
    Memory getMemory() { return memory; }
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
    virtual void execute(VoleMachine &machine) = 0;
};

class InstructionDecoder
{
public:
    bool validate(string code) {}
    Instruction *decode(string code) {}
};

class LoadInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

class StoreInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

class MoveInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

class ArithmeticLogicInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

class JumpInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

class HaltInstruction : public Instruction
{
public:
    void execute(VoleMachine &machine) override {}
};

int main()
{
    SimulatorUI ui;
    ui.start();
    return 0;
}
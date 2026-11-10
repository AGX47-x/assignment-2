#include "VoleMachine.h"
#include "Instruction.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

bool VoleMachine::loadProgram(std::string filepath, int startAddress)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        std::cout << "Could not open the file.\n";
        return false;
    }
    std::string line;
    int currentaddress = startAddress;
    while (getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty() || line[0] == ';')
            continue;
        if (line.length() >= 4)
        {
            try
            {
                std::string hex1 = line.substr(0, 2);
                std::string hex2 = line.substr(2, 2);
                memory.write(currentaddress, stoi(hex1, nullptr, 16));
                memory.write(currentaddress + 1, stoi(hex2, nullptr, 16));
                currentaddress += 2;
            }
            catch (...)
            {
            }
        }
    }
    pc = startAddress;
    halted = false;
    return true;
}

void VoleMachine::writeScreen(int value, int address)
{
    if (address == 0xFF)
    {
        if (value >= 32 && value <= 126)
        {
            screen += static_cast<char>(value);
        }
        else
        {
            screen += std::to_string(value) + " ";
        }
    }
    std::cout << "Screen Output: " << value << "\n";
}

bool VoleMachine::step()
{
    if (halted)
        return false;
    int highbyte = memory.read(pc);
    int lowbyte = memory.read(pc + 1);
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << highbyte
       << std::hex << std::setw(2) << std::setfill('0') << lowbyte;
    ir = ss.str();

    InstructionDecoder decoder;
    Instruction *inst = decoder.decode(ir);

    pc += 2;

    if (inst != nullptr)
    {
        inst->execute(*this);
        delete inst;
    }
    else
    {
        halted = true;
        return false;
    }
    return !halted;
}

void VoleMachine::run()
{
    while (!halted)
    {
        if (!step())
            break;
    }
}
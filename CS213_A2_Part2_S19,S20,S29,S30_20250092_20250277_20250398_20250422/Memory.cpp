#include "Memory.h"

int Memory::read(int address)
{
    if (address >= 0 && address < 256)
        return cells[address];
    return 0;
}

void Memory::write(int address, int value)
{
    if (address >= 0 && address < 256)
        cells[address] = value & 0xFF;
}
#include "Memory.h"

Memory::Memory()
{
    for (int i = 0; i < 256; i++)
    {
        cells[i] = 0;
    }
}

int Memory::read(int address)
{
    if (address >= 0 && address < 256)
    {
        return cells[address];
    }
    return 0;
}

void Memory::write(int address, int value)
{
    if (address >= 0 && address < 256)
    {
        cells[address] = value;
    }
}

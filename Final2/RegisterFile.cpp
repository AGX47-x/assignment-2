#include "RegisterFile.h"

int RegisterFile::read(int id)
{
    if (id >= 0 && id < 16)
    {
        if (id == 0)
            return 0;
        return registers[id];
    }
    return 0;
}

void RegisterFile::write(int id, int value)
{
    if (id == 0)
    {
        registers[0] = 0; // R0 is always 0
        return;
    }
    if (id > 0 && id < 16)
        registers[id] = value & 0xFF;
}
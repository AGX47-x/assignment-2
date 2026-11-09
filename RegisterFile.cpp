#include "RegisterFile.h"

RegisterFile::RegisterFile()
{
    for (int i = 0; i < 16; i++)
    {
        registers[i] = 0;
    }
}

int RegisterFile::read(int id)
{
    if (id >= 0 && id < 16)
    {
        return registers[id];
    }
    return 0;
}

void RegisterFile::write(int id, int value)
{
    if (id >= 0 && id < 16)
    {
        registers[id] = value;
    }
}

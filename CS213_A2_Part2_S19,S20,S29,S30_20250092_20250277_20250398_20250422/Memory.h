#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
    int cells[256] = {0};

public:
    int read(int address);
    void write(int address, int value);
};

#endif
#ifndef MEMORY_H
#define MEMORY_H

class Memory
{
private:
    int cells[256];

public:
    Memory();
    int read(int address);
    void write(int address, int value);
};

#endif

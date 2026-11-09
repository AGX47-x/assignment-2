#ifndef REGISTERFILE_H
#define REGISTERFILE_H

class RegisterFile
{
private:
    int registers[16];

public:
    RegisterFile();
    int read(int id);
    void write(int id, int value);
};

#endif

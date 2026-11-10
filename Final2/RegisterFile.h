#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

class RegisterFile
{
    int registers[16] = {0};

public:
    int read(int id);
    void write(int id, int value);
};

#endif
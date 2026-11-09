#pragma once
#include <string>
#include "Instruction.h"
class InstructionDecoder {
public:
    bool validate(std::string code);
    Instruction* decode(std::string code);
};

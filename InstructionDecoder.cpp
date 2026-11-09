#include "InstructionDecoder.h"
#include "LoadInstruction.h"
#include "StoreInstruction.h"
#include "MoveInstruction.h"
#include "ArithmeticLogicInstruction.h"
#include "JumpInstruction.h"
#include "HaltInstruction.h"
#include <string>

bool InstructionDecoder::validate(std::string code) {
    return code.length() == 4;
}

Instruction* InstructionDecoder::decode(std::string code) {
    if (!validate(code)) return nullptr;
    
    char opChar = code[0];
    int reg = std::stoi(code.substr(1, 1), nullptr, 16);
    int address = std::stoi(code.substr(2, 2), nullptr, 16);
    int op = std::stoi(std::string(1, opChar), nullptr, 16);
    
    if (op == 1) {
        return new LoadInstruction(reg, address);
    }
    else if (op == 2) {
        return new StoreInstruction(reg, address);
    }
    else if (op == 4) {
        int target = reg;
        int source = std::stoi(code.substr(3, 1), nullptr, 16);
        return new MoveInstruction(target, source);
    }
    else if (op >= 5 && op <= 9) {
        int r = reg;
        int s1 = std::stoi(code.substr(2, 1), nullptr, 16);
        int s2 = std::stoi(code.substr(3, 1), nullptr, 16);
        return new ArithmeticLogicInstruction(op, r, s1, s2);
    }
    else if (op == 0x0B) {
        return new JumpInstruction(reg, address);
    }
    else if (op == 0x0C) {
        return new HaltInstruction();
    }
    return nullptr;
}

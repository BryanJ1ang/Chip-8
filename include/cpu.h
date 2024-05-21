
#ifndef cpu_h
#define cpu_h

#include "memory.h"
#include "registers.h"
#include "display.h"
#include <iostream>
#include <stack>

class CPU {

    public:
        uint16_t fetch();
        void decodeExecute();

    private:
        Memory memory;
        Display display;
        Registers registers;
        std::stack<uint8_t> stack;

        uint16_t pc;
        uint16_t instruction;
        uint8_t operand; // first nibble
        uint8_t x; // second nibble - used for register
        uint8_t y; // third nibble - used for register
        uint8_t n; // fourth nibble
        uint8_t nn; // second byte (third and fourth nibble)
        uint8_t nnn; // second, third, fourth nibble (12 bits) memory address

};

#endif
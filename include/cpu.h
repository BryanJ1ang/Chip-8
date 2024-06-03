
#ifndef cpu_h
#define cpu_h

#include "memory.h"
#include "registers.h"
#include "display.h"
#include "timer.h"
#include <iostream>
#include <stack>

class CPU {

    public:
        void fetch();
        void decodeExecute();
        CPU();
        Memory memory;
        Display display;
        Timer timer;


    private:
        
        Registers registers;
        std::stack<uint16_t> stack; 

        uint16_t pc;
        uint16_t instruction;
        uint8_t operand; // first nibble
        uint8_t x; // second nibble - used for register
        uint8_t y; // third nibble - used for register
        uint8_t n; // fourth nibble
        uint8_t nn; // second byte (third and fourth nibble)
        uint16_t nnn; // second, third, fourth nibble (12 bits) memory address

        uint8_t keyTranslate(SDL_Keycode); // converts SDL keyboard event scanCode to Chip-8 key value


};

#endif
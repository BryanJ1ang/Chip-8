#include "cpu.h"
#include "memory.h"
#include "registers.h"

    uint16_t CPU::fetch() {
        uint8_t highByte = memory.read(pc);
        uint8_t lowByte = memory.read(pc + 1);

        instruction = ((uint16_t) Highbyte << 8) | (uint16_t) Lowbyte;
        pc += 2; // incrementing pc
    }

    void CPU::decodeExecute() {
        operand = (0xF000 & instruction) >> 12;
        x = (0x0F00 & instruction) >> 8;
        y = (0x00F0 & instruction) >> 4;
        n = 0x000F & instruction;
        nn = 0x00FF & instruction;
        nnn = 0x0FFF & instruction;

        switch(operand) {
            case 0x0: 
                //code block
                break;

            case 0x1: 
                //code block
                break;
            
            case 0x2: 
                //code block
                break;

            case 0x3: 
                //code block
                break;

            case 0x4: 
                //code block
                break;

            case 0x5: 
                //code block
                break;

            case 0x6: 
                //code block
                break;

            case 0x7: 
                //code block
                break;

            case 0x8: 
                //code block
                break;

            case 0x9: 
                //code block
                break;
            
            case 0xA: 
                //code block
                break;
                
            case 0xB: 
                //code block
                break;

            case 0xC: 
                //code block
                break;

            case 0xD: 
                //code block
                break;

            case 0xE: 
                //code block
                break;

            case 0xF: 
                //code block
                break;

                
            
        }

        
    }

    void CPU::execute() {

    }
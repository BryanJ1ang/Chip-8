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
                if (instruction == 0x00E8) {
                    display.clearDisplay();
                }
                break;

            case 0x1: 
                pc = nnn; // jump
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
                registers.write(x,nn); // set register value
                break;

            case 0x7: 
                registers.write(x, registers.read(x) + nn); // add nn to register 
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
                registers.setIndex(nnn);
                break;
                
            case 0xB: 
                //code block
                break;

            case 0xC: 
                //code block
                break;

            case 0xD: 
                // TODO: DRAW
                //code block
                int x = registers.read(CPU::x);
                int y = registers.read(CPU::y);
                int8_t mask = 0x1;
                uint8_t sprite_data;
                registers.write(0xf, 0);

                for (int sprite_height = 0; sprite_height < n; sprite_height++) {
                    for (int pixel_number = 7; pixel_number >= 0; pixel_number--) {
                        sprite_data = memory.read(registers.getIndex() + sprite_height);
                        uint8_t pixel = mask & (sprite_data >> pixel_number); 
                        if (pixel == 1) {
                            if (display.flipPixel((x + pixel_number) % 64, (y + sprite_height) % 32)) {
                                registers.write(0xf, 1);
                            }
                        }
                    }
                }

                break;

            case 0xE: 
                //code block
                break;

            case 0xF: 
                //code block
                break;

                
            
        }

        
    }

#include "cpu.h"
#include "memory.h"
#include <iomanip>
#include "registers.h"

     CPU::CPU() {
        std::stack<uint8_t> stack;
        pc = 0x200;
    }

    void CPU::fetch() {
        uint8_t highByte = memory.read(pc);
        uint8_t lowByte = memory.read(pc + 1);

        instruction = ((uint16_t) highByte << 8) | (uint16_t) lowByte;
        pc += 2; // incrementing pc
    }

    void CPU::decodeExecute() {
        std::cout << instruction << std::endl;
        operand = (0xF000 & instruction) >> 12;
        x = (0x0F00 & instruction) >> 8;
        y = (0x00F0 & instruction) >> 4;
        n = 0x000F & instruction;
        nn = 0x00FF & instruction;
        nnn = 0x0FFF & instruction;

            // std::cout << "x: 0x" 
            //   << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(x)
            //   << " y: 0x" 
            //   << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(y)
            //   << " n: 0x" 
            //   << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(n)
            //   << " nn: 0x"
            //   << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(nn)
            //   << " nnn: 0x"
            //   << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(nnn)
            //   << std::endl;

        switch(operand) {
            case 0x0: 
                if (instruction == 0x00E8) {
                    display.clearDisplay();
                }
                break;

            case 0x1: 
            std:: cout << "0x1 jumping nnn: " << nnn << std::endl;
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
                std:: cout << "0x6 set register nn: " << nn << std::endl;
                registers.write(x,nn); // set register value
                break;

            case 0x7: 
                std:: cout << "0x7 adding nn to register: " << nn << std::endl;

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
                {
                std::cout << "0xD draw instruction" << std::endl;
                    
                int x = registers.read(this->x);
                int y = registers.read(this->y);
                int8_t mask = 0x1;
                uint8_t sprite_data;
                registers.write(0xf, 0);
                // AAAA AAA=
                // 
                for (int sprite_height = 0; sprite_height < n; sprite_height++) {
                    for (int pixel_number = 7; pixel_number >= 0; pixel_number--) {
                        sprite_data = memory.read(registers.getIndex() + sprite_height);
                        uint8_t pixel = mask & (sprite_data >> pixel_number); 
                        std::cout << "about to draw: "<< pixel << std::endl;
                        if (pixel == 1) {
                            if (display.flipPixel((x + abs(pixel_number - 7)) % 64, (y + sprite_height) % 32)) {
                                registers.write(0xf, 1);
                            }
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

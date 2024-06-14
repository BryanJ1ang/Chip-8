#include "cpu.h"
#include "memory.h"
#include <iomanip>
#include "timer.h"
#include "registers.h"




     CPU::CPU() {
        pc = 0x200;
        key = 0xff;
    }

    void CPU::fetch() {
        std::cout << "memory read: 0x" 
        << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(pc) << std::endl;
        operand = (0xF000 & instruction) >> 12;        
        uint8_t highByte = memory.read(pc);
        uint8_t lowByte = memory.read(pc + 1);

        instruction = ((uint16_t) highByte << 8) | (uint16_t) lowByte;
        pc += 2; // incrementing pc
    }

    void CPU::decodeExecute() {
        std::cout << "instruction: 0x" 
        << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(instruction) << std::endl;
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
                if (instruction == 0x00E0) {
                    display.clearDisplay();
                } else if (instruction == 0x00ee) {
                    if (!stack.empty()) {
                        pc = stack.top();
                        stack.pop();
                        std::cout << "Returned to pc: " << pc << std::endl;
                    } else {
                        std::cerr << "Error: Attempt to return from subroutine without previous call!" << std::endl;
                    }
                }
                break;

            case 0x1: 
            std:: cout << "0x1 jumping nnn: " << nnn << std::endl;
                pc = nnn; // jump
                break;
            
            case 0x2: // branch
                std:: cout << "pushing stack : " << nnn << std::endl;
                stack.push(pc);
                pc = nnn;
                //code block
                break;

            case 0x3: // skip if x == nn
                    std::cout << static_cast<int>(registers.read(x)) << std::endl;
                if (registers.read(x) == nn) {
                    pc += 2;
                }
                break;

            case 0x4: // skip if x != nn
            std::cout << static_cast<int>(registers.read(x)) << std::endl;
                if (registers.read(x) != nn) {
                    pc += 2;
                }
                break;

            case 0x5: // skip if vx == vy
                if (registers.read(x) == registers.read(y)) {
                    pc += 2;
                }
                break;

            case 0x6: // set register
                registers.write(x,nn); // set register value
                break;

            case 0x7: // add to register
                registers.write(x, registers.read(x) + nn); // add nn to register 
                break;

            case 0x8: {
                uint8_t vx = registers.read(x);
                uint8_t vy = registers.read(y);
                if (n == 0) {
                    registers.write(x, registers.read(y));
                } else if (n == 1) { // bitwise OR
                    registers.write(x, vx | vy);
                } else if (n == 2) { // AND
                    registers.write(x, vx & vy);
                } else if (n == 3) { // XOR
                    registers.write(x, vx ^ vy);
                } else if (n == 4) { // ADD
                    registers.write(x, vy + vx);
                    if (255 - vx < vy) {
                        registers.write(0xf, 1);
                    } else {
                        registers.write(0xf, 0);
                    }
                } else if (n == 5) { // SUBTRACT vx - vy
                    registers.write(x, vx - vy);
                         if (vx >= vy) {
                        registers.write(0xf, 1);
                    } else {
                        registers.write(0xf, 0);
                    }
                } else if (n == 7) { // SUBTRACT vy - vx
                    registers.write(x, vy - vx);

                    if (vy >= vx) {
                        registers.write(0xf, 1);
                    } else {
                        registers.write(0xf, 0);
                    }               
                         
                } else if (n == 6) {
                    registers.write(x, vx >> 1);
                    registers.write(0xf, vx & 0x1);                    
                } else if (n == 0xE) {
                    registers.write(x, vx << 1);   
                    registers.write(0xf, (vx & 0x80) >> 7);                                    
                }
                break;
            }
            case 0x9: 
                if (registers.read(x) != registers.read(y)) {
                    pc += 2;
                }
                break;
            
            case 0xA: // set index register
                registers.setIndex(nnn);
                break;
                
            case 0xB: 
                pc = nnn + registers.read(x);
                break;

            case 0xC: {
                srand((unsigned) time(NULL));
                int random =  (rand() % 255);
                registers.write(x, random & nn);
            }
                break;

            case 0xD: 
                // TODO: DRAW
                //code block
                {
                    
                int x = registers.read(this->x) % 64;
                int y = registers.read(this->y) % 32;
                uint8_t sprite_data;
                registers.write(0xf, 0);
        
                for (int sprite_height = 0; sprite_height < n; sprite_height++) {
                    sprite_data = memory.read(registers.getIndex() + sprite_height);

                    for (int pixel_number = 7; pixel_number >= 0; pixel_number--) {
                        
                        uint8_t pixel = 0x1 & (sprite_data >> pixel_number); 
                            if (pixel == 1) {
                                if (display.flipPixel((x + 7 - pixel_number), (y + sprite_height))) {
                                    registers.write(0xf, 1);
                                }
                            }
                            if (x + 7 - pixel_number == 63) {
                                break;
                            }
                        }
                    if (y + sprite_height == 31) {
                        break;
                    }
                }
            }

            break;

            case 0xE: 
                if (nn == 0x9e) {
                            if (key == registers.read(x)) {
                                pc += 2;
                            }
                        
                    } else if (nn == 0xa1) {
                            if (key != registers.read(x)) {
                                pc += 2;
                            }
                    }
                    break;
        

            case 0xF:                    
                    if (nn == 0x0a) {
                        if (key == 0xff) {
                            pc -= 2;
                        } else {
                            registers.write(x, key);
                        }
                    } else if (nn == 0x07) {
                        registers.write(x, timer.delay_timer);
                        
                    } else if (nn == 0x15) {
                        timer.delay_timer = registers.read(x);
                    } else if (nn == 0x18) {
                        timer.sound_timer = registers.read(x);
                    } else if (nn == 0x1e) {
                        registers.setIndex(registers.getIndex() + registers.read(x));
                    } else if (nn == 0x29) {
                        registers.setIndex(0x50 + 5 * registers.read(x));
                    } else if (nn == 0x33) {
                        uint8_t vx = registers.read(x);
                        memory.write(registers.getIndex() + 2, vx % 10); // least significant decimal digit
                        memory.write(registers.getIndex() + 1, (vx / 10) % 10); // middle decimal digit
                        memory.write(registers.getIndex(), vx / 100); // most signficant decimal digit
                    } else if (nn == 0x55) {
                        for (uint8_t i = 0; i <= x; ++i) {
                            memory.write(registers.getIndex() + i, registers.read(i));
                        }

                    } else if (nn == 0x65) {
                        for (uint8_t i = 0; i <= x; ++i) {
                            registers.write(i, memory.read(registers.getIndex() + i));
        }

                    }
                    break;
                
        }
    }
    

uint8_t CPU::keyTranslate(SDL_Keycode key) {
    switch (key) {
        case SDLK_1: return 0x1; // '1'
        case SDLK_2: return 0x2; // '2'
        case SDLK_3: return 0x3; // '3'
        case SDLK_4: return 0xC; // '4'
        
        case SDLK_q: return 0x4; // 'Q'
        case SDLK_w: return 0x5; // 'W'
        case SDLK_e: return 0x6; // 'E'
        case SDLK_r: return 0xD; // 'R'
        
        case SDLK_a: return 0x7; // 'A'
        case SDLK_s: return 0x8; // 'S'
        case SDLK_d: return 0x9; // 'D'
        case SDLK_f: return 0xE; // 'F'
        
        case SDLK_z: return 0xA; // 'Z'
        case SDLK_x: return 0x0; // 'X'
        case SDLK_c: return 0xB; // 'C'
        case SDLK_v: return 0xF; // 'V' 

        default : return 0xff;
    }
}
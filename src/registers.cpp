    #include "registers.h"

    Registers::Registers() {
    }
     
    uint8_t Registers::read(uint8_t address) {
            return registers[address];
    }

    void Registers::write(uint8_t address, uint8_t data){
        if (address < 16) {
            registers[address] = data;
        }
    }

    void Registers::setIndex(uint16_t newIndex) {
        index = newIndex;
    }

    uint16_t Registers::getIndex() {
        return index;
    }

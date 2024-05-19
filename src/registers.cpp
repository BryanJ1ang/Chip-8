    #include "registers.h"
     
    uint8_t Registers::read(uint8_t address) {
        if (address < 16) {
            return registers[address];
        } else {
            // TODO: Exception handling out of bounds
        }
    }

    void Registers::write(uint8_t address, uint8_t data){
        if (address < 16) {
            registers[address] = data;
        } else {
            // TODO: Exception handling out of bounds
        }
    }
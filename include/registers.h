#ifndef registers_h
#define registers_h

#include <cstdint>

class Registers {

    public:
        uint8_t read(uint8_t address);
        void write(uint8_t address, uint8_t data);
        void setIndex(uint16_t newIndex);
        uint16_t Registers::getIndex();


    private:
        uint8_t registers[16];
        uint16_t index;

};

#endif
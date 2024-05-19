#ifndef registers_h
#define registers_h

#include <cstdint>

class Registers {

    public:
        uint8_t read(uint8_t address);
        void write(uint8_t address, uint8_t data);


    private:
        uint8_t registers[16];

};

#endif
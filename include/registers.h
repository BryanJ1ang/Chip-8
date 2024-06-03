#ifndef registers_h
#define registers_h

#include <cstdint>
#include <array>
#include <thread>
#include <chrono>

class Registers {

    public:
        uint8_t read(uint8_t address);
        void write(uint8_t address, uint8_t data);
        void setIndex(uint16_t newIndex);
        uint16_t getIndex();
        Registers();
  



    private:
        std::array<uint8_t, 16> registers;
        uint16_t index;

};

#endif
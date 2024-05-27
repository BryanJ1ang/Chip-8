#ifndef memory_h
#define memory_h
#include <cstdint>
#include <iostream>
#include <fstream>
#include <array>


class Memory {
    public:
    
        Memory(); 

        uint8_t read(uint16_t address);

        void write(uint16_t address, uint8_t data);

        void initialize_font();

        bool loadProgram(const std::string& filename);



    private:
    std::array<uint8_t, 4096> memory;

};

#endif 
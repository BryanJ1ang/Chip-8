#ifndef memory_h
#define memory_h
#include <cstdint>

class Memory {
    public:
    
        Memory(); 

        uint8_t read(uint16_t address);

        void write(uint16_t address, uint8_t data);

        void initialize_font();



    private:
        uint8_t memory[4096];



};

#endif 
#include <cstdint>
#include "memory.h"
#include <iostream>

    void Memory::initialize_font() {
        uint8_t fonts[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    int index = 0x50; // Starting index for the fonts in memory

    for (int i = 0; i < sizeof(fonts); i++) {
        write(index + i, fonts[i]); 
    }

    }

    Memory::Memory() {
        Memory::initialize_font();
        memory = {};
    }



    uint8_t Memory::read(uint16_t address) {
        if (address < 4095) {
            return memory[address];
        } else {
            return 0; // TODO: handle out of bounds
        }
    }

    void Memory::write(uint16_t address, uint8_t data) {
        if (address < 4095) {
            memory[address] = data;
        } else {
            // TODO: handle out of bounds
        }
    }

    bool Memory::loadProgram(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << '\n';
            return false;
        }

        // Go to the end of the file to determine its size
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Ensure the file is not too big for the available memory
        if (fileSize > sizeof(memory) - 0x200) {
            std::cerr << "ROM is too large to fit in memory\n";
            return false;
        }

        // Read the file contents into the memory starting at 0x200
        file.read(reinterpret_cast<char*>(&memory[0x200]), fileSize);

            if (file.gcount() != fileSize) {
        std::cerr << "Failed to read the entire file\n";
        return false;
    }
    
        file.close();
        return true;
    }

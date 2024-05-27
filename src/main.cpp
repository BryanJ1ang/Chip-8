#include "cpu.h"
#include "display.h"

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <SDL.h>
#include <thread>


using namespace std;

#ifdef main
#undef main
#endif 

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char *argv[]) {
    std::cout << "Starting Chip 8 Emulator" << std::endl;
    CPU cpu;

    if (!cpu.memory.loadProgram("D:\\vsC\\Chip-8\\chip8_programs\\IBM_Logo.ch8")) {
        std::cerr << "Error loading the CHIP-8 program.\n";
        return 0;
    }

    std::cout << "Program loaded" << std::endl;
    
    auto lastCycleTime = chrono::high_resolution_clock::now();
    int cycleDelay = 16;  // milliseconds

    while (cpu.display.isOpen()) { 
        auto currentTime = chrono::high_resolution_clock::now();
        float dt = chrono::duration<float, milli>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay) {
            lastCycleTime = currentTime;

            cout << "CPU Cycle" << endl;
            cpu.fetch();
            cpu.decodeExecute();
            cpu.display.update();
        
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    cpu.display.setClosed();
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
#include "cpu.h"
#include "display.h"
#include "timer.h"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <SDL.h>
#include <thread>
#include <chrono>

using namespace std;

#ifdef main
#undef main 
#endif 

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
std::string rom = "5-quirks.ch8";

int main(int argc, char *argv[]) {
    std::cout << "Starting Chip 8 Emulator" << std::endl;
    CPU cpu;

    if (!cpu.memory.loadProgram("D:\\vsC\\Chip-8\\chip8_programs\\" + rom)) {
        std::cerr << "Error loading the CHIP-8 program.\n";
        return 0;
    }
    std::cout << "Program loaded" << std::endl;

    
    auto lastCycleTime = chrono::high_resolution_clock::now();
    int cycleDelay = 16;  // milliseconds between CPU cycles
    float timerDelay = 1000 / 60;
    auto lastTimerUpdate = chrono::high_resolution_clock::now();

    while (cpu.display.isOpen()) {     
        auto currentTime = chrono::high_resolution_clock::now();
        auto dt = chrono::duration<float, milli>(currentTime - lastCycleTime).count();
        auto dtTimer = chrono::duration<float, milli>(currentTime - lastTimerUpdate).count();

        if (dtTimer > timerDelay) {
            lastTimerUpdate = currentTime;
            if (cpu.timer.delay_timer > 0) cpu.timer.delay_timer -= 1;
            if (cpu.timer.sound_timer > 0) {
                cpu.timer.sound_timer -= 1; // insert play beep
            }
        }

        if (dt > cycleDelay) {
            lastCycleTime = currentTime;

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
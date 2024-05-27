#ifndef display_h
#define display_h
#include <iostream>
#include <SDL.h>
#include <array>

class Display {
    public:
        void clearDisplay();
        Display();
        ~Display();
        void update();
        bool flipPixel(int x, int y);
        std::array<std::array<int, 32>, 64> colors;
        bool isOpen();
        void setClosed();


    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int screenWidth;
        int screenHeight;
        bool is_open;



};

#endif
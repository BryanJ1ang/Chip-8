#ifndef display_h
#define display_h
#include <SDL.h>
#include <array>

class Display {
    public:
        void clearDisplay();
        Display();
        ~Display();
        void update();
        bool isOpen();
        bool flipPixel(int x, int y);
        std::array<std::array<int, 32>, 64> colors;


    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int screenWidth;
        int screenHeight;
        SDL_Window *window; // SDL_createwindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 64,32, SDL_WINDOW_SHOWN)



};

#endif
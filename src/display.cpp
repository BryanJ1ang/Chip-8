#include "display.h"

    Display::Display() {
        screenWidth = 640;
        screenHeight = 320;

        colors = {};
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
             exit(1);
        }
        window = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (window == nullptr || renderer == nullptr) {
            std::cerr << "SDL_CreateWindow or SDL_CreateRenderer failed! SDL_Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(1);
        }
        is_open = true;
        clearDisplay();
        update();
    }

    Display::~Display() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Display::clearDisplay() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);    
    }

    bool Display::isOpen() {
    return is_open;
    }

    void Display::setClosed() {
        is_open = false;
    }

    void Display::update() {
        SDL_RenderPresent(renderer);
    }

    bool Display::flipPixel(int x, int y) {
        const int pixel_size = 10;
        SDL_Rect rect;
        rect.x = x * pixel_size;
        rect.y = y * pixel_size;
        rect.w = pixel_size;
        rect.h = pixel_size;
        bool flag = false;

        if (colors[x][y] == 1) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
            flag = true;
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        }
        SDL_RenderFillRect(renderer, &rect);
        colors[x][y] = !colors[x][y]; 
        return flag;
    }

    bool isWhite(int x, int y) {
        return false; // stub
    }



    
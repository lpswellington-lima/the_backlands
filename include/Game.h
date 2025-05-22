#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> // Include SDL_ttf for text rendering
#include <string>
#include "Character.h"

class Game {
public:
    Game();
    ~Game();
    void run();
    int deltaY = 0;
    int deltaX = 0;
    std::string animation_source = "Liya/right";
    int score = 0;

private:
    void processInput();
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font; // Font for rendering text
    SDL_Color textColor; // Color for the text
    bool running; // Flag to control the game loop
};

#endif // GAME_H
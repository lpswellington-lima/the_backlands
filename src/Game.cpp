#include "Game.h"
#include "graphics.h"
#include "config.h" // Including the configuration file
#include <iostream>
#include <thread> // For std::this_thread
#include <chrono> // For std::chrono

Game::Game() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        PRINT_ERROR("Error initializing SDL: " << SDL_GetError());
        running = false;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        PRINT_ERROR("Error initializing SDL_ttf: " << TTF_GetError());
        running = false;
    }

    // Load font
    font = TTF_OpenFont(TITLE_FONT, 48); // Provide the path to your .ttf font file
    if (!font) {
        PRINT_ERROR("Error loading font: " << TTF_GetError());
        running = false;
    }

    // Create window
    window = SDL_CreateWindow("SDL2 Window", 
                               SDL_WINDOWPOS_CENTERED, 
                               SDL_WINDOWPOS_CENTERED, 
                               SCREEN_WIDTH, SCREEN_HIGHT, 
                               SDL_WINDOW_SHOWN);
    if (!window) {
        PRINT_ERROR("Error creating window: " << SDL_GetError());
        running = false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        PRINT_ERROR("Error creating renderer: " << SDL_GetError());
        SDL_DestroyWindow(window);
        running = false;
    }

    running = true;

    PRINT("Window and renderer created successfully!");
}

Game::~Game() {
    TTF_CloseFont(font); // Close the font
    TTF_Quit(); // Quit SDL_ttf
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    PRINT("Destructor succeeded");
}

void Game::run() {
    while (running) {
        processInput();
        update();
        render();
    }
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_KEYDOWN){
            animation+=1;
            animation = (animation > 3) ? 1 : animation;
            switch (event.key.keysym.sym ){
                case SDLK_RIGHT:
                    animation_source = "Liya/right";
                    y_pos+=10;
                    if (y_pos > SCREEN_WIDTH){
                        y_pos = 0;
                        score += 1;
                    }
                    break;
                case SDLK_LEFT:
                    animation_source = "Liya/left";
                    y_pos-=10;
                    if (y_pos < 0){
                        y_pos = SCREEN_WIDTH;
                        score -= 1;
                    }
                    break;
                case SDLK_DOWN:
                    animation_source = "Liya/down";
                    x_pos+=10;
                    if (x_pos > SCREEN_HIGHT){
                        x_pos = 0;
                        score += 1;
                    }
                    break;
                case SDLK_UP:
                    animation_source = "Liya/up";
                    x_pos-=10;
                    if (x_pos < 0){
                        x_pos = SCREEN_HIGHT;
                        score -= 1;
                    }
                    break; 
            }
            
        }
    }
}

void Game::update() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    placeImage(renderer, "Assets/Images/"+animation_source+std::to_string(animation)+".png", y_pos, x_pos);
    

    // Set the color for the rectangle (example: light blue)
    SDL_Color rectColor = {117, 125, 119, 255}; // Light blue color
    
    // Draw a rectangle at position (100, 100) with width 200 and height 150
    drawRect(renderer, 0, 0, 300, 100, rectColor);
    

    textColor = {0, 0, 0, 255};
    renderText(renderer, "Score: " + std::to_string(score), 10, 10, font, textColor);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    
}

void Game::render() {
    SDL_RenderPresent(renderer);
}
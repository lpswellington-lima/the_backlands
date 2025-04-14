#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

// Function to draw a rectangle
void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color);

// Function to render text
void renderText(SDL_Renderer* renderer, const std::string& message, int x, int y, TTF_Font* font, SDL_Color color);

bool placeImage(SDL_Renderer* renderer, const std::string& imagePath, int x, int y);
#endif // GRAPHICS_H
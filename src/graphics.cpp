#include "graphics.h"
#include "config.h"
#include <iostream>

// Function to draw a rectangle
void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

// Function to render text
void renderText(SDL_Renderer* renderer, const std::string& message, int x, int y, TTF_Font* font, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
    if (!textSurface) {
        std::cerr << "Error creating text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!texture) {
        PRINT_ERROR("Error creating text texture: " << SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Get the dimensions of the texture
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Set up the destination rectangle for rendering
    SDL_Rect dstRect = { x, y, textWidth, textHeight };

    // Copy the texture to the rendering context
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    
    // Clean up
    SDL_FreeSurface(textSurface); // This line is redundant since the surface is already freed above
    SDL_DestroyTexture(texture);
}

bool placeImage(SDL_Renderer* renderer, const std::string& imagePath, int x, int y) {
    // Load image
    SDL_Surface* loadedSurface = IMG_Load(imagePath.c_str());
    if (!loadedSurface) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface); // Free the loaded surface after creating the texture
    if (!texture) {
        std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Get the texture dimensions
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    // Set up the destination rectangle
    SDL_Rect renderQuad = { x, y, width, height };

    // Render the texture to the screen
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
    
    // Free the texture
    SDL_DestroyTexture(texture);
    
    return true;
}
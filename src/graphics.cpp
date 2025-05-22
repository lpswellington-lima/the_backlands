#include "graphics.h"
#include "config.h"
#include <iostream>

// Function to draw a rectangle
void drawRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(renderer, &rect);
}

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
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

Image::Image(SDL_Renderer* renderer, const std::string& imagePath)
    : renderer(renderer), path(imagePath), texture(nullptr), width(0), height(0) {
    // Load the image and create the texture
    loadTexture();
}

// Method to load the image and create the texture
bool Image::loadTexture() {
    // Load image surface
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        return false;
    }

    // Create texture from surface
    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (!texture) {
        std::cerr << "Unable to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    // Set width and height based on the loaded surface
    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface); // Free surface
    return true;
}

// Method to place the image on the renderer at given coordinates
bool Image::place(int x, int y) { // Removed renderer parameter
    if (!texture) {
        std::cerr << "Texture not loaded!" << std::endl;
        return false;
    }

    // Set up the destination rectangle
    SDL_Rect renderQuad = { x, y, width, height };

    // Render the texture to the screen
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);

    return true;
}

// Get the width of the texture
int Image::getWidth() const {
    return width;
}

// Get the height of the texture
int Image::getHeight() const {
    return height;
}

// Free the texture resources
void Image::freeTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

// Destructor
Image::~Image() {
    freeTexture();
}

// Constructor to initialize the BlockSquare
BlockSquare::BlockSquare(int initX1, int initY1, int initX2, int initY2)
    : x1(initX1), y1(initY1), x2(initX2), y2(initY2) {}

// Method to calculate width
int BlockSquare::getWidth() const {
    return x2 - x1;
}

// Method to calculate height
int BlockSquare::getHeight() const {
    return y2 - y1;
}

// Method to print BlockSquare details
void BlockSquare::printDetails() const {
    std::cout << "BlockSquare: ("
              << x1 << ", " << y1 << ") to ("
              << x2 << ", " << y2 << "), Width: "
              << getWidth() << ", Height: "
              << getHeight() << std::endl;
}
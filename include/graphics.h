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

bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

class Image {
public:
    // Constructor
    Image(SDL_Renderer* renderer, const std::string& imagePath);

    // Method to place the image
    bool place(int x, int y);

    // Getters for image dimensions
    int getWidth() const;
    int getHeight() const;

    // Destructor
    ~Image();

private:
    SDL_Renderer* renderer; // Renderer as a member variable
    std::string path;  // Path to the image file
    SDL_Texture* texture; // Texture created from the image
    int width;          // Width of the texture
    int height;         // Height of the texture

    // Load the image into a texture
    bool loadTexture();

    // Free the texture resources
    void freeTexture();
};

class BlockSquare {
public:
    // Constructor to initialize the BlockSquare
    BlockSquare(int initX1, int initY1, int initX2, int initY2);

    // Getters for width and height
    int getWidth() const;
    int getHeight() const;

    // Method to print BlockSquare details
    void printDetails() const;

    int x1, y1; // Coordinates of the first point (top-left corner)
    int x2, y2; // Coordinates of the second point (bottom-right corner)
};

#endif // GRAPHICS_H
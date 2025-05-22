#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "graphics.h"  // Include the Image class
#include "config.h"

class GameObject {
public:
    // Constructor
    GameObject(int x, int y);

    // Virtual destructor
    virtual ~GameObject();

    // Pure virtual functions for derived classes to implement
    virtual void render() = 0;
    virtual void update() = 0;

    // Getter methods for width and height
    int getWidth() const;
    int getHeight() const;

    // Setters for width and height
    void setWidth(int w);
    void setHeight(int h);

protected:
    int posX; // X position
    int posY; // Y position
    int width; // Width of the object
    int height; // Height of the object
};

class StaticObject : public GameObject {
public:
    // Constructor
    StaticObject(int x, int y, const std::string& imagePath, SDL_Renderer* renderer, 
                 const BlockSquare& blockSquare); // Accept BlockSquare object

    // Override render and update
    void render() override;
    void render2();
    void update() override;

    // Destructor to free the Image
    ~StaticObject() override;

protected:
    Image* image;       // Pointer to the Image instance for rendering
    Image* image2;
    BlockSquare block;  // BlockSquare member variable
    SDL_Rect blocked;   // Used to manipulate the region blocked.
};

class Tree : public StaticObject {
public:
    // Constructor accepting BlockSquare
    Tree(int x, int y, SDL_Renderer* renderer, const std::string& imagePath, 
         const BlockSquare& blockSquare);

    // Override render method
    void render() override;
};

class Rock : public StaticObject {
public:
    // Constructor accepting BlockSquare
    Rock(int x, int y, SDL_Renderer* renderer, const std::string& imagePath, 
         const BlockSquare& blockSquare);

    // Override render method
    void render() override;
};

#endif // GAMEOBJECT_H
#include "Character.h"
#include "graphics.h"
#include "globals.h"
#include <iostream>
#include "config.h"

// Constructor
Character::Character(int hp, int posX, int posY, int spd)
    : health(hp), positionX(posX), positionY(posY), speed(spd) {

    }

// Getters
int Character::getHealth() const { return health; }
int Character::getPositionX() const { return positionX; }
int Character::getPositionY() const { return positionY; }

SDL_Rect Character::getRect() const {
    SDL_Rect rect = { positionX, positionY, width, height };
    return rect;
}

// Set position method
void Character::setPosition(int posX, int posY) {
    positionX = posX;
    positionY = posY;
}

// Move method
void Character::move(SDL_Renderer* renderer, int deltaX, int deltaY, std::string animation_source) {
    if (deltaX != 0 || deltaY != 0){
        animation+=1;
        animation = (animation > 3) ? 1 : animation;
    }
    Image sprite(renderer, "Assets/Images/"+animation_source+std::to_string(animation)+".png");
    width = sprite.getWidth();
    height = sprite.getHeight();

    SDL_Rect rect1 = { 200, 300, 50, 50 };
    canMove = true;

    SDL_Rect future;
    future.x = getRect().x + (deltaX * speed);
    future.y = getRect().y + (height/2) + (deltaY * speed);
    future.w = getRect().w;
    future.h = getRect().h/2;

    for (const auto& rect : g_rectangles) {
        if (checkCollision(rect, future)) {
            canMove = false;
            break;
        }
    }

    if(canMove){
        positionX += deltaX * speed;
        positionY += deltaY * speed;
    }
    sprite.place(positionX, positionY);
    PRINT("X: " << positionX << " Y: " << positionY << " # " << animation);
}

// Take damage method
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0; // Ensure health doesn't go below zero
    }
    std::cout << "Character takes " << damage << " damage! Health: " << health << std::endl;
}

// Is alive method
bool Character::isAlive() const {
    return health > 0;
}

// Virtual destructor
Character::~Character() {}
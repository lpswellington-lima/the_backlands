#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <SDL2/SDL.h>

class Character {
protected:
    int health;               // Character's health points
    int positionX;          // Character's X position
    int positionY;          // Character's Y position
    int speed;              // Movement speed
    int animation = 1;
    int width = 0;
    int height = 0;

public:
    // Constructor
    Character(int hp, int posX, int posY, int spd);

    // Getters
    int getHealth() const;
    int getPositionX() const;
    int getPositionY() const;
    SDL_Rect getRect() const;

    // Setters
    void setPosition(int posX, int posY); // Set the character's position

    // Method to move the character
    virtual void move(SDL_Renderer* renderer, int deltaX, int deltaY, std::string animation_source); 

    // Method to take damage
    void takeDamage(int damage);

    // Method to check if the character is alive
    bool isAlive() const;

    // Virtual destructor
    virtual ~Character();
};

#endif // CHARACTER_H
#include "GameObject.h"
#include <algorithm>
#include "globals.h"

// função de comparação personalizada
bool comparaRetangulos(const SDL_Rect& a, const SDL_Rect& b) {
    return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h;
}

// Constructor
GameObject::GameObject(int x, int y) : posX(x), posY(y), width(0), height(0) {}

// Virtual destructor
GameObject::~GameObject() {}

// Getter methods
int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

// Setters for width and height
void GameObject::setWidth(int w) {
    width = w;
}

void GameObject::setHeight(int h) {
    height = h;
}

// Constructor
StaticObject::StaticObject(int x, int y, const std::string& imagePath, SDL_Renderer* renderer, 
                           const BlockSquare& blockSquare) 
    : GameObject(x, y), 
      image(new Image(renderer, imagePath)),
      block(blockSquare) { // Initialize BlockSquare with the provided object
    // Optionally set width and height based on the image

    std::string newImagePath = "";
    int pos = imagePath.rfind(".png");
    if (pos != std::string::npos && pos == imagePath.length() - 4) {
        // Replace ".png" with "_f.png"
        newImagePath = imagePath.substr(0, pos) + "_f.png";
        PRINT(newImagePath);
    }

    image2 = new Image(renderer, newImagePath);
    setWidth(image->getWidth());
    setHeight(image->getHeight());
    blocked.x = block.x1 + x;
    blocked.y = block.y1 + y;
    blocked.w = std::abs(block.x2 - block.x1);
    blocked.h = std::abs(block.y2 - block.y1);
    PRINT("StaticObject blocked area x = " << blocked.x << " y = " << blocked.y << " w = " << blocked.w << " h = " << blocked.h);
    g_rectangles.push_back(blocked);
}

// Static objects typically don't change their state, so update does nothing
void StaticObject::update() {
    // No update needed for static objects
}

// Render the static object
void StaticObject::render() {
    if (image) {
        image->place(posX, posY); // Render using the Image class
    }
}

void StaticObject::render2() {
    if (image) {
        image2->place(posX, posY); // Render using the Image class
    }
}

// Destructor to free the Image
StaticObject::~StaticObject() {
    delete image; // Free the allocated Image instance
    delete image2;// Free the allocated Image instance
    //PRINT("Static object destructed!");
    auto it = std::find_if(g_rectangles.begin(), g_rectangles.end(),
                       [&](const SDL_Rect& rect) { return comparaRetangulos(rect, blocked); });
    if (it != g_rectangles.end()) {
        g_rectangles.erase(it);
    }
}

// Constructor
Tree::Tree(int x, int y, SDL_Renderer* renderer, const std::string& imagePath,
           const BlockSquare& blockSquare) 
    : StaticObject(x, y, imagePath, renderer, blockSquare) {
    // Optionally set more specifics if needed
}

// Render the tree using the inherited render method
void Tree::render() {
    StaticObject::render(); // Calls the render method of StaticObject
}

// Constructor
Rock::Rock(int x, int y, SDL_Renderer* renderer, const std::string& imagePath,
           const BlockSquare& blockSquare) 
    : StaticObject(x, y, imagePath, renderer, blockSquare) {
    // Optionally set more specifics if needed
}

// Render the rock using the inherited render method
void Rock::render() {
    StaticObject::render(); // Calls the render method of StaticObject
}



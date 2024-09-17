#pragma once
#include <raylib.h>
#include <iostream>

class Room {
public:
    Color color;
    int width;
    int height;

    float posX;
    float posY;

    Room(float roomX, float roomY);

    void Draw();
};


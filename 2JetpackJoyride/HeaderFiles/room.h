#pragma once
#include <raylib.h>

class Room {
public:
    Color color;
    int width;
    int height;

    float posX;
    float posY;

    Image image;
    Texture2D background;

    Room(float roomX, float roomY);

    void Draw();
};


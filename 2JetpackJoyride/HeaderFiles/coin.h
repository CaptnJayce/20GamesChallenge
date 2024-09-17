#pragma once
#include <raylib.h>

class Coin {
public:
    int value;
    float posX;
    float posY;
    int radius;
    Color color;

    Coin(float coinX, float coinY);
    void Draw();
};


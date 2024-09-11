#pragma once
#include <raylib.h>

class Player {
public:
    float width;
    float height;
    float speed;
    float posX;
    float posY;

    Player(float startX, float startY);
    void Draw();
    void Update(int upKey, int downKey);
};


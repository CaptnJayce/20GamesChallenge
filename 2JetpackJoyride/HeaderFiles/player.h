#pragma once
#include <raylib.h>

class Player {
public:
    int moveUp;
    float speed;
    float posX;
    float posY;
    int height;
    int width;
    Color color;

    Player(float playerX, float playerY);
    void Draw();
    void Update(int moveUp);
};

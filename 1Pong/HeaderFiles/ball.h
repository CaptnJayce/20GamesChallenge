#pragma once
#include <raylib.h>

class Ball {
public:
    float centerX;
    float centerY;
    int radius;
    int speedY;
    int speedX;
    int score1;
    int score2;

    Ball(float startX, float startY);
    void Draw();
    void Update();
};

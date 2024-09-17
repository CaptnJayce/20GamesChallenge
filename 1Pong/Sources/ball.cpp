#include "HeaderFiles/ball.h"
#include <raylib.h>

extern float screenHeight;
extern float screenWidth;
extern Color white;

Ball::Ball(float startX, float startY) {
    centerX = startX;
    centerY = startY;
    speedX = 7;
    speedY = 7;
    radius = 20;
    score1 = 0;
    score2 = 0;
    sound1 = LoadSound("Sounds/collision.wav");
    sound2 = LoadSound("Sounds/score.wav");
}

void Ball::Draw() {
    DrawCircle(centerX, centerY, radius, white);
}

void Ball::Update() {
    centerX += speedX;
    centerY += speedY;

    // Collision
    if (centerY + radius >= screenHeight || centerY - radius <= 0) {
        speedY *= -1;
        PlaySound(sound1);
    }
    if (centerX + radius >= screenWidth || centerX - radius <= 0) {
        speedX *= -1;
        PlaySound(sound1);
    }

    // Scoring
    if (centerX + radius >= screenWidth) {
        score2++;
        PlaySound(sound2);
    }
    if (centerX - radius <= 0) {
        score1++;
        PlaySound(sound2);
    }
}

#include "HeaderFiles/player.h"
#include <raylib.h>

extern float screenHeight;
extern Color white;

Player::Player(float startX, float startY) {
    width = 20;
    height = 100;
    speed = 10.0;
    posX = startX;
    posY = startY;
}

void Player::Draw() {
    DrawRectangle(posX, posY, width, height, white);
}

void Player::Update(int upKey, int downKey) {
    if (posY >= screenHeight - height) {
        posY = screenHeight - height;
    }
    if (posY <= 0) {
        posY = 0;
    }

    if (IsKeyDown(upKey)) {
        posY -= speed;
    }

    if (IsKeyDown(downKey)) {
        posY += speed;
    }
}

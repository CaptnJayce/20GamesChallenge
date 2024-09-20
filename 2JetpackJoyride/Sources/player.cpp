#include "../HeaderFiles/player.h"
#include <raylib.h>

extern int screenHeight;

Player::Player(float playerX, float playerY) {
    height = 60;
    width = 40;
    speed = 400;
    posX = playerX;
    posY = playerY;
    color = {240, 15, 15, 50};
}

void Player::Draw() {
    DrawRectangle(posX, posY, width, height, color);
}

void Player::Update(int moveUp) {
    float dt = GetFrameTime();

    posX += speed * dt;

    if (IsKeyDown(moveUp)) {
        posY -= speed * dt;
    } else {
        posY += 400 * dt;
    }

    if (posY >= screenHeight - (80 + height)) {
        posY = screenHeight - (80 + height);
    }

    if (posY <= 80) {
        posY = 80;
    }
}

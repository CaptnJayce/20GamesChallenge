#include "../HeaderFiles/player.h"
#include "../HeaderFiles/gamelogic.h"
#include <iostream>
#include <raylib.h>

Player::Player(float playerX, float playerY) {
  height = 60;
  width = 40;
  speed = 400;
  posX = playerX;
  posY = playerY;
  color = {240, 15, 15, 50};
  dist = 0;
  toSpawn = 0;
  alive = true;
}

void Player::Draw() { DrawRectangle(posX, posY, width, height, color); }

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

  // pick to spawn coins or lasers
  if (dist > 200 && speed < 600) {
    srand(time(0));
    toSpawn = (rand() % 2) + 1;
    dist = 0;

    // speed "curve"
    if (speed < 1200) {
      speed += 25;
    }
  }

  // spawn objects quicker as speed increases
  if (dist > 100 && speed >= 600) {
    srand(time(0));
    toSpawn = (rand() % 2) + 1;
    dist = 0;

    if (speed < 1200) {
      speed += 25;
    }
  }

  dist++;
}

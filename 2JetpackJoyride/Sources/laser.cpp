#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <vector>

Laser::Laser(float laserX, float laserY) : isRotated(false) {
  posX = laserX;
  posY = laserY;
  width = 40.0;
  height = 185.0;
  color = {0, 255, 0, 50};
}

void Laser::Draw() { DrawRectangle(posX, posY, width, height, color); }

void Laser::Update(Player &player, std::vector<Laser> &laser) {
  if (player.toSpawn == 2) {
    srand(time(0));
    const int laserPattern = (rand() % 3) + 1;
    const float laserHeight = ((float)rand() / (float)RAND_MAX) * (700.0 - 100.0) + 100.0;

    if (laserPattern == 1) {
      laser.push_back(Laser(player.posX + 1300, 100));
    }

    if (laserPattern == 2) {
      laser.push_back(Laser(player.posX + 1300, 500));
    }

    if (laserPattern == 3) {
      std::cout << "spawning laser pattern 3" << std::endl;
      Laser newLaser(player.posX + 1300, laserHeight);
      newLaser.isRotated = true;
      laser.push_back(newLaser);
    }

    player.toSpawn = 0;
  }

  // Collisions
  for (auto it = laser.begin(); it != laser.end();) {
    Rectangle laserRect = {it->posX, it->posY, it->width, it->height};

    if (it->isRotated) {
      laserRect = {it->posX - 190, it->posY + 12, it->height, it->width};
    }

    if (CheckCollisionRecs(laserRect, (Rectangle){player.posX, player.posY, (float)player.width, (float)player.height})) {
      it = laser.erase(it);
      player.alive = false;
    } else {
      ++it;
    }
  }
}

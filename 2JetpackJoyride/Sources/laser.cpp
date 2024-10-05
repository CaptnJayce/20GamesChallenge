#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <vector>

Laser::Laser(float laserX, float laserY) {
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
    const int laserPattern = (rand() % 1) + 1;

    // LASER SPAWNER
    if (laserPattern == 1) {
      std::cout << "spawning laser pattern 1" << std::endl;
      laser.push_back(Laser(player.posX + 1300, 100));
    }

    if (laserPattern == 2) {
      std::cout << "spawning laser pattern 2" << std::endl;
    }

    player.toSpawn = 0;
  }

  // Collisions
  for (auto it = laser.begin(); it != laser.end();) {
    if (CheckCollisionRecs(
            (Rectangle){it->posX, it->posY, it->width, it->height},
            (Rectangle){player.posX, player.posY, (float)player.width,
                        (float)player.height})) {
      it = laser.erase(it);
    } else {
      ++it;
    }
  }
}

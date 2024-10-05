#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <vector>

Laser::Laser(float laserX, float laserY) {
  posX = laserX;
  posY = laserY;
  width = 50;
  height = 200;

  color = {0, 255, 0, 50};
}

void Laser::Draw() { DrawRectangle(posX, posY, width, height, color); }

void Laser::Update(Player &player, std::vector<Laser> &laser) {

  if (player.dist > 200) {
    srand(time(0));

    const int laserPattern = (rand() % 2) + 1;

    // LASER SPAWNER
    if (laserPattern == 4) {
      std::cout << "spawning laser pattern 1" << std::endl;
      laser.push_back(Laser(player.posX + 1200 + 100, 700.0));
    }

    if (laserPattern == 5) {
      std::cout << "spawning laser pattern 2" << std::endl;
    }

    player.dist = 0;
  }

  // Collisions
  /*
  for (auto it = coin.begin(); it != coin.end();) {
    if (CheckCollisionCircleRec((Vector2){it->posX, it->posY}, it->radius,
                                (Rectangle){player.posX, player.posY,
                                            (float)player.width,
                                            (float)player.height})) {
      it = coin.erase(it);
      total += 1;
    } else {
      ++it;
    }
  }
  */
}

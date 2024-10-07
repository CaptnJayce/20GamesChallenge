#pragma once
#include "player.h"
#include <raylib.h>
#include <vector>

class Laser {
public:
  float posX;
  float posY;
  float width;
  float height;
  bool isRotated;

  Color color;

  Laser(float laserX, float laserY);
  void Draw();
  void Update(Player &player, std::vector<Laser> &laser);
};

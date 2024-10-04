#pragma once
#include "player.h"
#include <raylib.h>
#include <vector>

class Entity {
public:
  int value;
  float posX;
  float posY;
  int radius;
  int total;

  Color color;

  Entity(float coinX, float coinY);
  void Draw();
  void Update(Player &player, std::vector<Entity> &obstacle,
              std::vector<Entity> &coin);
};

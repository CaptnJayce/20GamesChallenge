#pragma once
#include "player.h"
#include <raylib.h>
#include <vector>

class Coin {
public:
  int value;
  float posX;
  float posY;
  int radius;
  int total;

  Color color;

  Coin(float coinX, float coinY);
  void Draw();
  void Update(Player &player, std::vector<Coin> &coin);
};

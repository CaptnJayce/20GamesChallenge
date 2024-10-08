#pragma once
#include "../HeaderFiles/coin.h"
#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/room.h"
#include "../HeaderFiles/textures.h"
#include <iostream>
#include <raylib.h>
#include <vector>

extern int screenWidth;
extern int screenHeight;

class GameLogic {
public:
  int totalDistance;

  GameLogic();
  void Draw();
  void Update();

  void DrawRoofAndFloor(std::vector<Room> &roof, std::vector<Room> &floor, Textures &sprite);
  void DrawCoins(std::vector<Coin> &coins, Textures &sprite);
  void DrawLasers(std::vector<Laser> &lasers, Textures &sprite);
};

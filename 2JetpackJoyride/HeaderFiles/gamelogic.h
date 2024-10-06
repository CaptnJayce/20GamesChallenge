#pragma once

extern int screenWidth;
extern int screenHeight;

class GameLogic {
public:
  int totalDistance;

  GameLogic();

  void Draw();
  void Update();
};

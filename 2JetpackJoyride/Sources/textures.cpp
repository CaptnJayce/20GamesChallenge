#include "../HeaderFiles/textures.h"
#include <raylib.h>

Textures::Textures() {
  playerTexture = LoadTexture("../Sprites/jetpackjimmy.png");
  coinTexture = LoadTexture("../Sprites/coin.png");
  backgroundTexture = LoadTexture("../Backgrounds/background1.png");
  floorTexture = LoadTexture("../Backgrounds/floor.png");
  roofTexture = LoadTexture("../Backgrounds/roof.png");
  laserTexture = LoadTexture("../Sprites/obstacle.png");
}

#include "../HeaderFiles/coin.h"
#include "../HeaderFiles/player.h"
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <vector>

Coin::Coin(float obstX, float obstY) {
  posX = obstX;
  posY = obstY;
  radius = 15;
  value = 1;
  total = 0;

  color = {0, 255, 0, 50};
}

void Coin::Draw() { DrawCircle(posX, posY, radius, color); }

void Coin::Update(Player &player, std::vector<Coin> &coin) {

  if (player.toSpawn == 1) {
    srand(time(0));

    const int coinsToSpawn = (rand() % 5) + 1;
    const int coinPattern = (rand() % 3) + 1;
    int coinSpacing = 50;
    const float coinHeight = ((float)rand() / (float)RAND_MAX) * (700.0 - 100.0) + 100.0;

    // COIN SPAWNER
    // Straight line
    if (coinPattern == 1) {
      std::cout << "spawning coin 1" << std::endl;
      for (int i = 0; i < coinsToSpawn; i++) {
        coin.push_back(Coin(player.posX + 1300 + coinSpacing, coinHeight));
        coinSpacing += 50;
      }
    }

    // Diagonal down
    if (coinPattern == 2) {
      std::cout << "spawning coin 2" << std::endl;

      for (int i = 0; i < coinsToSpawn; i++) {
        coin.push_back(Coin(player.posX + 1300 + coinSpacing, 100.0 + coinSpacing));
        coinSpacing += 50;
      }
    }

    // Diagonal up
    if (coinPattern == 3) {
      std::cout << "spawning coin 3" << std::endl;

      for (int i = 0; i < coinsToSpawn; i++) {
        coin.push_back(Coin(player.posX + 1300 + coinSpacing, 700.0 - coinSpacing));
        coinSpacing += 50;
      }
    }

    player.toSpawn = 0;
  }

  // Collisions
  for (auto it = coin.begin(); it != coin.end();) {
    if (CheckCollisionCircleRec((Vector2){it->posX, it->posY}, it->radius, (Rectangle){player.posX, player.posY, (float)player.width, (float)player.height})) {
      it = coin.erase(it);
      total += 1;
    } else {
      ++it;
    }
  }
}

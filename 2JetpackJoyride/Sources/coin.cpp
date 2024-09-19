#include "../HeaderFiles/coin.h"
#include <cstdlib>
#include <iostream>

Coin::Coin(float coinX, float coinY) : posX(coinX), posY(coinY), radius(20), value(1), color(YELLOW){}

void Coin::Draw() {
    DrawCircle(posX, posY, radius, color);
}

void coinSpawner(Player& player, std::vector<Coin>& coins) {
    srand(time(0));

    const int coinsToSpawn = (rand() % 5) + 1;
    const int coinPattern = (rand() % 3) + 1;
    int coinSpacing = 50;
    const float coinHeight = ((float)rand() / (float)RAND_MAX) * (700.0 - 100.0) + 100.0;

    std::cout << coinsToSpawn << std::endl;

    // Straight line
    if (coinPattern == 1) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back(Coin(player.posX + 1200 + 100 + coinSpacing, coinHeight));
            coinSpacing += 50;
        }
    }
    // Diagonal down
    else if (coinPattern == 2) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back(Coin(player.posX + 1200 + 100 + coinSpacing, 100.0 + coinSpacing));
            coinSpacing += 50;
        }
    }
    // Diagonal up
    else if (coinPattern == 3) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back(Coin(player.posX + 1200 + 100 + coinSpacing, 700.0 - coinSpacing));
            coinSpacing += 50;
        }
    }
}

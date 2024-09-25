#include "../HeaderFiles/coin.h"
#include "../HeaderFiles/player.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <raylib.h>

Coin::Coin(float coinX, float coinY) {
    posX = coinX;
    posY = coinY;
    radius = 20;
    value = 1;
    total = 0;

    color = {0, 255, 0, 50};
}

void Coin::Draw() {
    DrawCircle(posX, posY, radius, color);
}

void Coin::Update(Player& player, std::vector<Coin>& coins) {
    if (player.dist > 200) {
        srand(time(0));

        const int coinsToSpawn = (rand() % 5) + 1;
        const int coinPattern = (rand() % 3) + 1;
        int coinSpacing = 50;
        const float coinHeight = ((float)rand() / (float)RAND_MAX) * (700.0 - 100.0) + 100.0;

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
        player.dist = 0;
    }

    // Collisions
    for (auto it = coins.begin(); it != coins.end();) {
        if (CheckCollisionCircleRec((Vector2){it->posX, it->posY}, it->radius, (Rectangle){player.posX, player.posY, (float)player.width, (float)player.height})) {
            it = coins.erase(it);
            total += 1;
        }
        else {
            ++it;
        }
    }
}


#pragma once
#include <raylib.h>
#include <vector>
#include "player.h"

class Coin {
public:
    int value;
    float posX;
    float posY;
    int radius;
    Color color;

    Coin(float coinX, float coinY);
    void Draw();
};

void coinSpawner(Player& player, std::vector<Coin>& coins);

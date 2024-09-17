#include "HeaderFiles/coin.h"
#include <raylib.h>

Coin::Coin(float coinX, float coinY) {
    value = 1;
    posX = coinX;
    posY = coinY;
    radius = 20;
    color = {255, 255, 0, 255};
}

void Coin::Draw() {
    DrawCircle(posX, posY, radius, color);
}

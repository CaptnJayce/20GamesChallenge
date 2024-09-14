#include "HeaderFiles/room.h"
#include <raylib.h>

Room::Room(float roomX, float roomY) {
    height = 40;
    width = 2000;
    posX = roomX;
    posY = roomY;
    color = {255, 255, 255, 255};
}

void Room::Draw() {
    DrawRectangle(posX, posY, width, height, color);
}



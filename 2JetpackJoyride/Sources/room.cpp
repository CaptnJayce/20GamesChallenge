#include "../HeaderFiles/room.h"
#include <raylib.h>

Room::Room(float roomX, float roomY) {
    height = 40;
    width = 2000;
    posX = roomX;
    posY = roomY;
    image = LoadImage("../Backgrounds/background1.png");
    background = LoadTextureFromImage(image);
}

void Room::Draw() {
    DrawRectangle(posX, posY, width, height, WHITE);
}

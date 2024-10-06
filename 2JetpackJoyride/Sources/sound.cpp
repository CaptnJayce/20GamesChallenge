#include "../HeaderFiles/sound.h"
#include <raylib.h>

Sounds::Sounds() {
  pressed = LoadSound("../Sounds/soundTest.mp3");
  coinPickup = LoadSound("../Sounds/coin_pickup_1.wav");

  muted = false;
  volume = 0.2;
}

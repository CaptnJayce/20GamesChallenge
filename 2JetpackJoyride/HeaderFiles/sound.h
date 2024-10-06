#pragma once
#include <raylib.h>

class Sounds {
public:
  Sound pressed;
  Sound coinPickup;
  bool muted;
  float volume;

  Sounds();
};

#include "../HeaderFiles/gamelogic.h"
#include "../HeaderFiles/coin.h"
#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/room.h"

int screenWidth = 1200;
int screenHeight = 800;

GameLogic::GameLogic() {}

void GameLogic::Draw() {}

void GameLogic::Update() {}

// Draw roof and floor
void GameLogic::DrawRoofAndFloor(std::vector<Room> &roof,
                                 std::vector<Room> &floor, Textures &sprite) {
  for (size_t i = 0; i < roof.size(); i++) {
    roof[i].Draw();
    DrawTextureEx(sprite.backgroundTexture,
                  Vector2{roof[i].posX, roof[i].posY + 40}, 0, 2, WHITE);
    DrawTextureEx(sprite.floorTexture, Vector2{floor[i].posX, floor[i].posY}, 0,
                  2, WHITE);
    DrawTextureEx(sprite.roofTexture, Vector2{roof[i].posX, roof[i].posY}, 0, 2,
                  WHITE);
  }
}

// Draw coins
void GameLogic::DrawCoins(std::vector<Coin> &coins, Textures &sprite) {
  for (auto &coin : coins) {
    coin.Draw();
    DrawTextureEx(
        sprite.coinTexture,
        Vector2{
            static_cast<float>(coin.posX - (sprite.coinTexture.height / 4.0)),
            static_cast<float>(coin.posY - (sprite.coinTexture.width / 4.0))},
        0, 0.5, WHITE);
  }
}

// Draw lasers
void GameLogic::DrawLasers(std::vector<Laser> &lasers, Textures &sprite) {
  for (auto &laser : lasers) {
    if (laser.isRotated) {
      DrawTextureEx(sprite.laserTexture,
                    Vector2{static_cast<float>(laser.posX),
                            static_cast<float>(laser.posY)},
                    90.0f, 4, WHITE);

    } else {
      laser.Draw();
      DrawTextureEx(
          sprite.laserTexture,
          Vector2{static_cast<float>(laser.posX -
                                     (sprite.laserTexture.height / 4.0)),
                  static_cast<float>(laser.posY -
                                     (sprite.laserTexture.width / 4.0))},
          0, 4, WHITE);
    }
  }
}

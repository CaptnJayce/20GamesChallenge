#include <algorithm>
#include <cstdlib>
#include <raylib.h>
#include <vector>

#include "../HeaderFiles/coin.h"
#include "../HeaderFiles/gamelogic.h"
#include "../HeaderFiles/laser.h"
#include "../HeaderFiles/player.h"
#include "../HeaderFiles/room.h"
#include "../HeaderFiles/sound.h"
#include "../HeaderFiles/textures.h"

using namespace std;

enum GameScreen { MENU, GAME, GAME_OVER };

int prevTotal;

int spacing;

vector<Coin> coins;
vector<Laser> lasers;
Coin coin(50, 50);
Laser laser(50, 50);
Player player(50, 600);

int main() {
  InitAudioDevice();
  Sounds sound;
  GameLogic game;
  SetMasterVolume(sound.volume);

  GameScreen currentScreen = MENU;

  vector<Room> roof;
  vector<Room> floor;

  Camera2D camera = {0};
  camera.offset = (Vector2){screenWidth / 10.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  InitWindow(screenWidth, screenHeight, "Jetpack Joyride Clone");
  SetTargetFPS(60);

  Textures sprite;

  while (WindowShouldClose() == false) {
    if (currentScreen == MENU) {
      if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(sound.pressed);
        currentScreen = GAME;
      }

      if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
      }

      if (IsKeyReleased(KEY_M)) {
        if (sound.muted == false) {
          SetMasterVolume(0);
          sound.muted = true;
        } else {
          SetMasterVolume(sound.volume);
          sound.muted = false;
        }
      }
    }

    if (currentScreen == GAME) {
      if (IsKeyPressed(KEY_BACKSPACE)) {
        currentScreen = MENU;
      }
    }

    if (currentScreen == GAME_OVER) {
      DrawText("Game Over!", screenWidth / 2 - MeasureText("Main Menu", 60) / 2,
               50, 60, WHITE);
    }

    if (player.alive == false) {
      currentScreen = GAME_OVER;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    if (currentScreen == MENU) {
      DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 60) / 2,
               50, 60, WHITE);
      DrawRectangle(screenWidth / 3, 110, screenWidth / 3, 4, WHITE);
      DrawText("Press Enter to Play",
               screenWidth / 2 - MeasureText("Press Enter to Play", 30) / 2,
               screenHeight / 2, 30, WHITE);
      DrawText("Press Escape to Quit",
               screenWidth / 2 - MeasureText("Press Escape to Quit", 30) / 2,
               screenHeight / 2 + 40, 30, WHITE);
      DrawText("Press M to Mute",
               screenWidth / 2 - MeasureText("Press M to Mute", 30) / 2,
               screenHeight / 2 + 80, 30, WHITE);
    }

    if (currentScreen == GAME) {
      prevTotal = coin.total;

      game.Update();
      player.Update(KEY_SPACE);
      coin.Update(player, coins);
      laser.Update(player, lasers);

      if (coin.total > prevTotal) {
        PlaySound(sound.coinPickup);
      }

      camera.target = (Vector2){player.posX + 20, screenHeight / 2.0f};

      if (player.posX + screenWidth > spacing) {
        roof.push_back({Room(0 + spacing, 40)});
        floor.push_back({Room(0 + spacing, screenHeight - 80)});
        spacing += 2000;
      }

      // check if vector is empty and if its far enough off-screen to not
      // be seen when unloading
      if (!roof.empty() &&
          roof.front().posX + 2000 < player.posX - screenWidth / 10.0f) {
        roof.erase(roof.begin());
        floor.erase(floor.begin());
      }

      if (!coins.empty()) {
        coins.erase(remove_if(coins.begin(), coins.end(),
                              [&](const Coin &coin) {
                                return coin.posX <
                                       player.posX - screenWidth / 10.0f;
                              }),
                    coins.end());
      }

      BeginMode2D(camera);

      // GAME LOGIC
      for (size_t i = 0; i < roof.size(); i++) {
        roof[i].Draw();
        floor[i].Draw();

        DrawTextureEx(sprite.backgroundTexture,
                      Vector2{roof[i].posX, roof[i].posY + 40}, 0, 2, WHITE);
        DrawTextureEx(sprite.floorTexture,
                      Vector2{floor[i].posX, floor[i].posY}, 0, 2, WHITE);
        DrawTextureEx(sprite.roofTexture, Vector2{roof[i].posX, roof[i].posY},
                      0, 2, WHITE);
      }

      for (size_t i = 0; i < coins.size(); i++) {
        coins[i].Draw();
        DrawTextureEx(
            sprite.coinTexture,
            Vector2{static_cast<float>(coins[i].posX -
                                       (sprite.coinTexture.height / 4.0)),
                    static_cast<float>(coins[i].posY -
                                       (sprite.coinTexture.width / 4.0))},
            0, 0.5, WHITE);
      }

      for (size_t i = 0; i < lasers.size(); i++) {
        lasers[i].Draw();
        DrawTextureEx(
            sprite.laserTexture,
            Vector2{static_cast<float>(lasers[i].posX -
                                       (sprite.laserTexture.height / 4.0)),
                    static_cast<float>(lasers[i].posY -
                                       (sprite.laserTexture.width / 4.0))},
            0, 4, WHITE);
      }

      player.Draw();
      DrawTextureEx(sprite.playerTexture,
                    Vector2{player.posX - 10, player.posY - 5}, 0, 1, WHITE);
      EndMode2D();

      // draws in screen space after camera has ended
      DrawText(TextFormat("%i", coin.total), screenWidth / 2, screenHeight - 20,
               20, WHITE);
      DrawText(TextFormat("%i", game.totalDistance / 10), screenWidth / 4,
               screenHeight - 20, 20, WHITE);
    }

    EndDrawing();
  }

  CloseAudioDevice();
  UnloadTexture(sprite.playerTexture);
  CloseWindow();
}

// TO DO //

// REFACTORING
// Camera
// Texture Handling

// IMPLEMENTATION
// Sounds
// Floor + Roof Textures
// Backgrounds
// Speed Curve

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <vector>

#include "../HeaderFiles/entity.h"
#include "../HeaderFiles/player.h"
#include "../HeaderFiles/room.h"

using namespace std;

enum GameScreen { MENU, GAME, GAME_OVER };

int screenWidth = 1200;
int screenHeight = 800;

int prevTotal;

int spacing;

int totalDistance;

float volume = 0.2;

vector<Entity> coins;
vector<Entity> obstacles;
Entity coin(50, 50);
Entity obstacle(50, 50);
Player player(50, 600);

int main() {
  InitAudioDevice();
  SetMasterVolume(volume);

  Sound pressed = LoadSound("../Sounds/soundTest.mp3");
  Sound coinPickup = LoadSound("../Sounds/coin_pickup_1.wav");

  GameScreen currentScreen = MENU;

  vector<Room> roof;
  vector<Room> floor;

  Camera2D camera = {0};
  camera.offset = (Vector2){screenWidth / 10.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  cout << "Starting Game" << endl;
  InitWindow(screenWidth, screenHeight, "Jetpack Joyride Clone");
  SetTargetFPS(60);

  Texture2D playerTexture = LoadTexture("../Sprites/jetpackjimmy.png");
  Texture2D coinTexture = LoadTexture("../Sprites/coin.png");
  Texture2D backgroundTexture = LoadTexture("../Backgrounds/background1.png");
  Texture2D floorTexture = LoadTexture("../Backgrounds/floor.png");
  Texture2D roofTexutre = LoadTexture("../Backgrounds/roof.png");

  while (WindowShouldClose() == false) {
    if (currentScreen == MENU) {
      if (IsKeyPressed(KEY_ENTER)) {
        PlaySound(pressed);
        currentScreen = GAME;
      }

      if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
      }
    }

    if (currentScreen == GAME) {
      if (IsKeyPressed(KEY_BACKSPACE)) {
        currentScreen = MENU;
      }
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

      player.Update(KEY_SPACE);
      coin.Update(player, obstacles, coins);

      if (coin.total > prevTotal) {
        PlaySound(coinPickup);
      }

      /* cout << player.dist << endl; */
      totalDistance += 1;

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

      if (!obstacles.empty()) {
        obstacles.erase(remove_if(obstacles.begin(), obstacles.end(),
                                  [&](const Entity &obstacle) {
                                    return obstacle.posX <
                                           player.posX - screenWidth / 10.0f;
                                  }),
                        obstacles.end());
      }

      BeginMode2D(camera);

      for (int i = 0; i < roof.size(); i++) {
        roof[i].Draw();
        floor[i].Draw();

        DrawTextureEx(backgroundTexture,
                      Vector2{roof[i].posX, roof[i].posY + 40}, 0, 2, WHITE);
        DrawTextureEx(floorTexture, Vector2{floor[i].posX, floor[i].posY}, 0, 2,
                      WHITE);
        DrawTextureEx(roofTexutre, Vector2{roof[i].posX, roof[i].posY}, 0, 2,
                      WHITE);
      }

      for (int i = 0; i < coins.size(); i++) {
        coins[i].Draw();
        DrawTextureEx(
            coinTexture,
            Vector2{
                static_cast<float>(coins[i].posX - (coinTexture.height / 2.0)),
                static_cast<float>(coins[i].posY - (coinTexture.width / 2.0))},
            0, 1, WHITE);
      }

      player.Draw();
      DrawTextureEx(playerTexture, Vector2{player.posX - 10, player.posY - 5},
                    0, 1, WHITE);
      EndMode2D();

      // draws in screen space after camera has ended
      DrawText(TextFormat("%i", coin.total), screenWidth / 2, screenHeight - 20,
               20, WHITE);
      DrawText(TextFormat("%i", totalDistance / 10), screenWidth / 4,
               screenHeight - 20, 20, WHITE);
    }

    EndDrawing();
  }

  CloseAudioDevice();
  UnloadTexture(playerTexture);
  CloseWindow();
}

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <vector>

#include "../HeaderFiles/room.h"
#include "../HeaderFiles/player.h"
#include "../HeaderFiles/coin.h"

using namespace std;

enum GameScreen { MENU, GAME, GAME_OVER };

int screenWidth = 1200;
int screenHeight = 800;

int spacing;

int dist = 0;
int coinDist = 200;

int totalCoins = 0;
int totalDistance;

vector<Coin> coins;
Player player(50, 600);
Coin coin(50, 50);

// checks for collision with coins
// thank you chatGPT lol
void checkPlayerCoinCollision(Player &player) {
    for (auto it = coins.begin(); it != coins.end();) {
        if (CheckCollisionCircleRec((Vector2){it->posX, it->posY}, it->radius, (Rectangle){player.posX, player.posY, (float)player.width, (float)player.height})) {
            totalCoins += coin.value;
            it = coins.erase(it);
        }
        else {
            ++it;
        }
    }
}


int main() {
    GameScreen currentScreen = MENU;

    vector<Room> roof;
    vector<Room> floor;

    Camera2D camera = { 0 };
    camera.offset = (Vector2) {
        screenWidth/10.0f, screenHeight/2.0f
    };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    cout << "Starting Game" << endl;
    InitWindow(screenWidth, screenHeight, "Jetpack Joyride Clone");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        if (currentScreen == MENU) {
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = GAME;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                CloseWindow();
            }
        } else if (currentScreen == GAME) {
            if (IsKeyPressed(KEY_BACKSPACE)) {
                currentScreen = MENU;
            }
        }
        
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentScreen == MENU) {
            DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 20) / 2, screenHeight / 2 - 40, 20, DARKGRAY);
            DrawText("Press Enter to Play", screenWidth / 2 - MeasureText("Press Enter to Play", 20) / 2, screenHeight / 2, 20, GRAY);
            DrawText("Press Escape to Quit", screenWidth / 2 - MeasureText("Press Escape to Quit", 20) / 2, screenHeight / 2 + 40, 20, GRAY);
        } else if (currentScreen == GAME) {
            // Game rendering goes here
            player.Update(KEY_SPACE);

            dist += 1;
            totalDistance += 1;

            camera.target = (Vector2) {
                player.posX + 20, screenHeight / 2.0f
            };

            checkPlayerCoinCollision(player);

            if (player.posX + screenWidth > spacing) {
                roof.push_back({Room(0 + spacing, 40)});
                floor.push_back({Room(0 + spacing, screenHeight - 80)});
                spacing += 2000;
            }

            // check if vector is empty and if its far enough off-screen to not be seen when unloading
            if (!roof.empty() && roof.front().posX + 2000 < player.posX - screenWidth / 10.0f) {
                roof.erase(roof.begin());
                floor.erase(floor.begin());
            }

            if (dist > coinDist) {
                dist = 0;
                coinSpawner(player, coins);
            }

            BeginMode2D(camera);

            for (int i = 0; i < roof.size(); i++) {
                roof[i].Draw();
                floor[i].Draw();
            }

            for (int i = 0; i < coins.size(); i++) {
                coins[i].Draw();
            }

            player.Draw();
            EndMode2D();

            // draws in screen space after camera has ended
            DrawText(TextFormat("%i", totalCoins), screenWidth/2, screenHeight - 20, 20, WHITE);
            DrawText(TextFormat("%i", totalDistance / 10), screenWidth/4, screenHeight - 20, 20, WHITE);

        }

        EndDrawing();
    }

    CloseWindow();
}


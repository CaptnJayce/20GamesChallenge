#include <cstdlib>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <vector>

#include "../HeaderFiles/room.h"
#include "../HeaderFiles/player.h"
#include "../HeaderFiles/coin.h"

using namespace std;

int screenWidth = 1200;
int screenHeight = 800;

int spacing;
int coinSpacing = 40;

int dist = 0;
int coinDist = 200;

int totalCoins = 0;

vector<Coin> coins;
Player player(50, 600);

// checks for collision with coins
// thank you chatGPT lol
void checkPlayerCoinCollision(Player &player) {
    for (auto it = coins.begin(); it != coins.end();) {
        if (CheckCollisionCircleRec((Vector2){it->posX, it->posY}, it->radius, (Rectangle){player.posX, player.posY, (float)player.width, (float)player.height})) {
            totalCoins += 1;
            it = coins.erase(it);
        }
        else {
            ++it;
        }
    }
}

// this could likely be optimised a lot
void coinSpawner() {
    srand(time(0));

    const int coinsToSpawn = (rand() % 5) + 1;
    const int coinPattern = (rand() % 3) + 1;
    const float coinHeight = ((float)rand() / (float)RAND_MAX) * (700.0 - 100.0) + 100.0;

    cout << coinsToSpawn << endl;

    // Straight line
    if (coinPattern == 1) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back({Coin((player.posX + screenWidth) + 100 + coinSpacing, coinHeight)});
            coinSpacing += 50;
        }
        coinSpacing = 50;
    }

    // Diagonal down
    if (coinPattern == 2) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back({Coin((player.posX + screenWidth) + 100 + coinSpacing, 100.0 + coinSpacing)});
            coinSpacing += 50;
        }
        coinSpacing = 50;
    }

    // Diagonal up
    if (coinPattern == 3) {
        for (int i = 0; i < coinsToSpawn; i++) {
            coins.push_back({Coin((player.posX + screenWidth) + 100 + coinSpacing, 700.0 - coinSpacing)});
            coinSpacing += 50;
        }
        coinSpacing = 50;
    }
}

int main() {
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
        player.Update(KEY_SPACE);

        dist += 1;

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
            coinSpawner();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        for (int i = 0; i < roof.size(); i++) {
            roof[i].Draw();
            floor[i].Draw();
        }

        for (int i = 0; i < coins.size(); i++) {
            coins[i].Draw();
        }

        // coin score
        player.Draw();
        EndMode2D();

        // draws in screen space after camera has ended
        DrawText(TextFormat("%i", totalCoins), screenWidth/2, screenHeight - 20, 20, {255, 255, 255, 255});
        EndDrawing();
    }

    CloseWindow();
}


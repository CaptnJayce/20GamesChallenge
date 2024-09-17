#include <cstdlib>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <vector>

#include "HeaderFiles/room.h"
#include "HeaderFiles/player.h"
#include "HeaderFiles/coin.h"

using namespace std;

int screenWidth = 1200;
int screenHeight = 800;

int spacing;
int coinSpacing = 40;

vector<Coin> coins;

void coinSpawner() {
    srand(time(0));

    int coinsToSpawn = (rand() % 5) + 1;
    cout << coinsToSpawn << endl;

    for (int i = 0; i < coinsToSpawn; i++) {
        coins.push_back({Coin(100 + coinSpacing, 200)});
        coinSpacing += 100;
    }
}

int main() {
    vector<Room> roof;
    vector<Room> floor;

    Player player(50, 600);

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

        camera.target = (Vector2) {
            player.posX + 20, screenHeight / 2.0f
        };

        if (player.posX + screenWidth > spacing) {
            roof.push_back({Room(0 + spacing, 40)});
            floor.push_back({Room(0 + spacing, screenHeight - 80)});
            spacing += 2000;
            coinSpawner();
        }

        // check if vector is empty and if its far enough off screen to not be seen when unloading
        if (!roof.empty() && roof.front().posX + 2000 < player.posX - screenWidth / 10.0f) {
            roof.erase(roof.begin());
            floor.erase(floor.begin());
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

        player.Draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
}

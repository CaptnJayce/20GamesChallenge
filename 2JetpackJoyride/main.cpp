#include <iostream>
#include <raylib.h>

#include "HeaderFiles/room.h"
#include "HeaderFiles/player.h"

using namespace std;

int screenWidth = 1200;
int screenHeight = 800;

int main() {
    Room roof(0, 40);
    Room floor(0, screenHeight - 80);
    Player player(50, 600);

    Camera2D camera = { 0 };
    camera.offset = (Vector2) {
        screenWidth/2.0f, screenHeight/2.0f
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

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        floor.Draw();
        roof.Draw();
        player.Draw();
        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
}

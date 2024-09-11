#include <iostream>
#include <raylib.h>
#include "HeaderFiles/player.h"
#include "HeaderFiles/ball.h"

using namespace std;

Color black = {0, 0, 0, 255};
Color white = {255, 255, 255, 255};

float screenHeight = 750;
float screenWidth = 1200;

int main() {
    Player player1(40, screenHeight / 2 - 50);
    Player player2(screenWidth - 60, screenHeight / 2 - 50);
    Ball ball(screenWidth / 2, screenHeight / 2);

    int font = 20;

    cout << "Starting Game" << endl;
    InitWindow(screenWidth, screenHeight + 50, "Pong");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Updating
        player1.Update(KEY_W, KEY_S);
        player2.Update(KEY_UP, KEY_DOWN);
        ball.Update();

        // Drawing
        player1.Draw();
        player2.Draw();
        ball.Draw();

        // Collision
        if (CheckCollisionCircleRec(Vector2{ball.centerX, ball.centerY}, ball.radius, Rectangle{player1.posX, player1.posY, player1.width, player1.height})) {
            ball.speedX *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.centerX, ball.centerY}, ball.radius, Rectangle{player2.posX, player2.posY, player2.width, player2.height})) {
            ball.speedX *= -1;
        }

        ClearBackground(black);

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, white);                             // Middle Line
        DrawLine(screenWidth, screenHeight, 0, screenHeight, white);                                    // Bottom Line
        DrawText(TextFormat("%i", ball.score1), screenWidth - 200, screenHeight + 15, font, white);     // Game Score 1
        DrawText(TextFormat("%i", ball.score2), 200, screenHeight + 15, font, white);                   // Game Score 2
        DrawText("Player 1", 15, screenHeight + 15, font, white);                                       // Player 1
        DrawText("Player 2", screenWidth - 100, screenHeight + 15, font, white);                        // Player 2

        EndDrawing();
    }

    CloseWindow();
}


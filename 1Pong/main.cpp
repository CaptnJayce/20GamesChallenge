#include <iostream>
#include <raylib.h>
using namespace std;

Color black = {0, 0, 0, 255};
Color white = {255, 255, 255, 255};

// floats as they are used for calculation and can cause inaccuracy
// im unsure of the severity of said inaccuracy but errors annoy me xd

float screenHeight = 750;
float screenWidth = 1200;

class Player {
public:
    float width = 20;
    float height = 100;
    float speed = 10.0;
    float posX = 40;
    float posY = screenHeight / 2 - (height / 2);

    void Draw() {
        DrawRectangle(posX, posY, width, height, white);
    }

    void Update() {
        if(posY >= screenHeight - height) {
            posY = screenHeight - height;
        }
        if(posY <= 0) {
            posY = 0;
        }

        if(IsKeyDown(KEY_W)) {
            cout << "Moving Player 1" << endl;
            posY = posY - speed;
        }

        if(IsKeyDown(KEY_S)) {
            cout << "Moving Player 1" << endl;
            posY = posY + speed;
        }
    }
};

class Player2 {
public:
    float width = 20;
    float height = 100;
    float speed = 10.0;
    float posX = screenWidth - (40 + width);
    float posY = screenHeight / 2 - (height / 2);

    void Draw() {
        DrawRectangle(posX, posY, width, height, white);
    }

    void Update() {
        if(posY >= screenHeight - height) {
            posY = screenHeight - height;
        }
        if(posY <= 0) {
            posY = 0;
        }

        if(IsKeyDown(KEY_UP)) {
            cout << "Moving Player 2" << endl;
            posY = posY - speed;
        }

        if(IsKeyDown(KEY_DOWN)) {
            cout << "Moving Player 2" << endl;
            posY = posY + speed;
        }
    }
};

class Ball {
public:
    float centerX = screenWidth / 2;
    float centerY = screenHeight / 2;
    int radius = 20;
    int speedY = 7;
    int speedX = 7;
    int score1 = 0;
    int score2 = 0;

    Player player = Player();
    Player2 player2 = Player2();

    void Draw() {
        DrawCircle(centerX, centerY, radius, white);
    }

    void Update() {
        centerX += speedX;
        centerY += speedY;

        // Collision
        if (centerY + radius >= screenHeight || centerY - radius <= 0) {
            speedY *= -1;
        }
        if (centerX + radius >= screenWidth || centerX - radius <= 0) {
            speedX *= -1;
        }

        // Scoring
        if (centerX + radius >= screenWidth) {
            score2++;
        }
        if (centerX - radius <= 0) {
            score1++;
        }
    }
};

int main() {
    Player player = Player();
    Player2 player2 = Player2();
    Ball ball = Ball();

    int font = 20;

    cout << "Starting Game" << endl;
    InitWindow(screenWidth, screenHeight + 50, "Pong");
    SetTargetFPS(60);

    while(WindowShouldClose() == false) {
        BeginDrawing();

        // Updating
        player.Update();
        player2.Update();
        ball.Update();

        // Drawing
        player.Draw();
        player2.Draw();
        ball.Draw();

        // Collision
        if(CheckCollisionCircleRec(Vector2{ball.centerX, ball.centerY}, ball.radius, Rectangle{player.posX, player.posY, player.width, player.height})) {
            ball.speedX *= -1;
        };

        if(CheckCollisionCircleRec(Vector2{ball.centerX, ball.centerY}, ball.radius, Rectangle{player2.posX, player2.posY, player2.width, player2.height})) {
            ball.speedX *= -1;
        };

        ClearBackground(black);

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, white);                             // Middle Line
        DrawLine(screenWidth, screenHeight, 0, screenHeight, white);                                    // Bottom Line
        DrawText(TextFormat("%i", ball.score1),  screenWidth - 200, screenHeight + 15, font, white);    // Game Score 1
        DrawText(TextFormat("%i", ball.score2),  200, screenHeight + 15, font, white);                  // Game Score 2
        DrawText("Player 1", 15, screenHeight + 15, font, white);                                       // Player 1
        DrawText("Player 2", screenWidth - 100, screenHeight + 15, font, white);                        // Player 2
        EndDrawing();
    }

    CloseWindow();
}

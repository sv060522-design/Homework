#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 2");
    SetTargetFPS(60);

    float x = 50.0f;
    float y = screenHeight / 2.0f;
    float r = 30.0f;
    float speed = 5.0f;

    while (!WindowShouldClose()) {
        x += speed;
        if (x - r > screenWidth) {
            x = -r;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle((int)x, (int)y, r, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
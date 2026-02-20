#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 7");
    SetTargetFPS(60);

    Vector2 pos = { 400.0f, 300.0f };
    float radius = 30.0f;
    float speed = 5.0f;
    Color color = WHITE;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) pos.x += speed;
        if (IsKeyDown(KEY_LEFT)) pos.x -= speed;
        if (IsKeyDown(KEY_UP)) pos.y -= speed;
        if (IsKeyDown(KEY_DOWN)) pos.y += speed;

        if (IsKeyPressed(KEY_SPACE)) {
            color.r = GetRandomValue(0, 255);
            color.g = GetRandomValue(0, 255);
            color.b = GetRandomValue(0, 255);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(pos, radius, color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
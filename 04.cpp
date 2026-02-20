#include "raylib.h"
#include <cmath>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 4");
    SetTargetFPS(60);

    Vector2 center = { 400.0f, 300.0f };
    float orbitRadius = 200.0f;
    float smallRadius = 20.0f;
    float angle = 0.0f;
    float speed = 2.0f;

    while (!WindowShouldClose()) {
        angle += speed * DEG2RAD;

        float x = center.x + orbitRadius * cosf(angle);
        float y = center.y + orbitRadius * sinf(angle);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircleLines((int)center.x, (int)center.y, orbitRadius, GRAY);
        DrawCircleV({ x, y }, smallRadius, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
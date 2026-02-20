#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 6");
    SetTargetFPS(60);

    Rectangle rect = { 300.0f, 200.0f, 200.0f, 150.0f };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        Color color = CheckCollisionPointRec(mouse, rect) ? RED : GREEN;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRec(rect, color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
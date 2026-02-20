#include "raylib.h"
#include <cmath>

int main() {
    const int w = 800;
    const int h = 600;
    InitWindow(w, h, "Task 8a");
    SetTargetFPS(60);

    Vector2 pos = { 400, 300 };
    float r = 20;
    float speed = 3;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 dir = { mouse.x - pos.x, mouse.y - pos.y };
            float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
            if (len > 0.1f) {
                dir.x /= len;
                dir.y /= len;
                pos.x += dir.x * speed;
                pos.y += dir.y * speed;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(pos, r, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include "raylib.h"
#include <cmath>

int main() {
    const int w = 800;
    const int h = 600;
    InitWindow(w, h, "Task 8b");
    SetTargetFPS(60);

    Vector2 pos = { 400, 300 };
    Vector2 vel = { 0, 0 };
    float r = 20;
    float accel = 0.2f;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 dir = { mouse.x - pos.x, mouse.y - pos.y };
            float len = sqrtf(dir.x*dir.x + dir.y*dir.y);
            if (len > 0.1f) {
                dir.x /= len;
                dir.y /= len;
                vel.x += dir.x * accel;
                vel.y += dir.y * accel;
            }
        }

        pos.x += vel.x;
        pos.y += vel.y;

        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(pos, r, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
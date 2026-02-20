#include "raylib.h"
#include <cmath>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 3");
    SetTargetFPS(60);

    Vector2 pivot = { 400.0f, 300.0f };
    float side = 150.0f;
    float angle = 0.0f;
    float rotationSpeed = 2.0f;

    while (!WindowShouldClose()) {
        angle += rotationSpeed;

        Vector2 localV0 = { 0, 0 };
        Vector2 localV1 = { side, 0 };
        Vector2 localV2 = { side, side };
        Vector2 localV3 = { 0, side };

        auto rotate = [&](Vector2 local) -> Vector2 {
            float rad = angle * DEG2RAD;
            return {
                pivot.x + local.x * cosf(rad) - local.y * sinf(rad),
                pivot.y + local.x * sinf(rad) + local.y * cosf(rad)
            };
        };

        Vector2 r0 = rotate(localV0);
        Vector2 r1 = rotate(localV1);
        Vector2 r2 = rotate(localV2);
        Vector2 r3 = rotate(localV3);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLineV(r0, r1, WHITE);
        DrawLineV(r1, r2, WHITE);
        DrawLineV(r2, r3, WHITE);
        DrawLineV(r3, r0, WHITE);

        DrawCircleV(pivot, 5, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
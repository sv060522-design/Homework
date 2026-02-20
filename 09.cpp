#include "raylib.h"
#include <vector>

struct Ball {
    Vector2 pos;
    Color col;
};

int main() {
    const int w = 800;
    const int h = 600;
    InitWindow(w, h, "Task 9");
    SetTargetFPS(60);

    std::vector<Ball> balls;

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ball b;
            b.pos = GetMousePosition();
            b.col = WHITE;
            balls.push_back(b);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& b : balls) {
                b.col.r = GetRandomValue(0, 255);
                b.col.g = GetRandomValue(0, 255);
                b.col.b = GetRandomValue(0, 255);
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (const auto& b : balls) {
            DrawCircleV(b.pos, 20, b.col);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include "raylib.h"
#include <string>

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Task 5");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        Vector2 windowPos = GetWindowPosition();
        int absX = static_cast<int>(windowPos.x + mouse.x);
        int absY = static_cast<int>(windowPos.y + mouse.y);

        std::string text = "Window: " + std::to_string(static_cast<int>(mouse.x)) + ", " + std::to_string(static_cast<int>(mouse.y)) +
                           " | Absolute: " + std::to_string(absX) + ", " + std::to_string(absY);

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText(text.c_str(), 50, 300, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
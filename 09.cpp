#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <cmath>
#include <list>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>

struct Ball
{
    Vector2 position;
    float radius;
    bool isChoosen;
    Color color;

    Ball(Vector2 p, float r, Color c = WHITE) : position(p), radius(r), isChoosen(false), color(c) {}

    void draw() const
    {
        DrawCircleV(position, radius, color);

        if (isChoosen)
        {
            const float f = 0.7f;

            DrawLineV({position.x - radius, position.y + radius}, {position.x - radius, position.y + radius*f}, WHITE);
            DrawLineV({position.x - radius, position.y + radius}, {position.x - radius*f, position.y + radius}, WHITE);

            DrawLineV({position.x + radius, position.y + radius}, {position.x + radius, position.y + radius*f}, WHITE);
            DrawLineV({position.x + radius, position.y + radius},{position.x + radius*f, position.y + radius}, WHITE);

            DrawLineV({position.x + radius, position.y - radius}, {position.x + radius*f, position.y - radius}, WHITE);
            DrawLineV({position.x + radius, position.y - radius}, {position.x + radius, position.y - radius*f}, WHITE);

            DrawLineV({position.x - radius, position.y - radius}, {position.x - radius*f, position.y - radius}, WHITE);
            DrawLineV({position.x - radius, position.y - radius}, {position.x - radius, position.y - radius*f}, WHITE);
        }
    }
};

Color randomColor() {
    return { (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255 };
}

struct ContextMenu {
    bool isOpen = false;
    Vector2 position;
    std::vector<std::string> items = { "Delete", "Create", "Random Color", "Increase", "Decrease", "Copy", "Cut", "Paste" };
    int hovered = -1;
};

int main()
{
    srand(time(NULL));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(800, 600, "Select, Move, Delete!");
    SetTargetFPS(60);

    std::list<Ball> balls;
    balls.emplace_back(Vector2{200, 200}, 26, randomColor());
    balls.emplace_back(Vector2{400, 300}, 20, randomColor());
    balls.emplace_back(Vector2{500, 100}, 16, randomColor());
    balls.emplace_back(Vector2{200, 400}, 18, randomColor());
    balls.emplace_back(Vector2{350, 150}, 22, randomColor());
    balls.emplace_back(Vector2{750, 400}, 21, randomColor());

    Rectangle selectionRect{0, 0, 0, 0};
    bool isSelecting = false;
    bool isDragging = false;
    Vector2 previousMouse{0, 0};

    std::vector<Ball> clipboard;
    Vector2 copyCenter{0, 0};

    ContextMenu menu;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (menu.isOpen)
            {
                Rectangle menuRect = { menu.position.x, menu.position.y, 150, (float)menu.items.size() * 20.f };
                if (CheckCollisionPointRec(mouse, menuRect))
                {
                    int index = (int)((mouse.y - menu.position.y) / 20);
                    if (index >= 0 && index < (int)menu.items.size())
                    {
                        std::string item = menu.items[index];
                        if (item == "Delete")
                        {
                            for (auto it = balls.begin(); it != balls.end(); )
                            {
                                if (it->isChoosen) it = balls.erase(it);
                                else ++it;
                            }
                        }
                        else if (item == "Create")
                        {
                            balls.emplace_back(menu.position, 5 + GetRandomValue(0, 39), randomColor());
                        }
                        else if (item == "Random Color")
                        {
                            for (auto& b : balls) if (b.isChoosen) b.color = randomColor();
                        }
                        else if (item == "Increase")
                        {
                            for (auto& b : balls) if (b.isChoosen) b.radius *= 1.25f;
                        }
                        else if (item == "Decrease")
                        {
                            for (auto& b : balls) if (b.isChoosen) b.radius *= 0.75f;
                        }
                        else if (item == "Copy" || item == "Cut")
                        {
                            clipboard.clear();
                            Vector2 center = { 0, 0 };
                            int count = 0;
                            for (const auto& b : balls)
                            {
                                if (b.isChoosen)
                                {
                                    clipboard.push_back(b);
                                    center = Vector2Add(center, b.position);
                                    count++;
                                }
                            }
                            if (count > 0) copyCenter = Vector2Scale(center, 1.0f / count);
                            if (item == "Cut")
                            {
                                for (auto it = balls.begin(); it != balls.end(); )
                                {
                                    if (it->isChoosen) it = balls.erase(it);
                                    else ++it;
                                }
                            }
                        }
                        else if (item == "Paste")
                        {
                            if (!clipboard.empty())
                            {
                                Vector2 delta = Vector2Subtract(menu.position, copyCenter);
                                for (const auto& cb : clipboard)
                                {
                                    balls.emplace_back(Vector2Add(cb.position, delta), cb.radius, cb.color);
                                }
                            }
                        }
                    }
                }
                menu.isOpen = false;
                continue;
            }

            // Find if hit any ball
            bool hitAny = false;
            bool hitSelected = false;
            auto hitIt = balls.end();
            for (auto it = balls.begin(); it != balls.end(); ++it)
            {
                if (Vector2Distance(mouse, it->position) < it->radius)
                {
                    hitAny = true;
                    hitIt = it;
                    hitSelected = it->isChoosen;
                    break;
                }
            }

            if (!IsKeyDown(KEY_LEFT_CONTROL))
            {
                bool shouldDeselect = true;
                if (hitAny && hitSelected) shouldDeselect = false;
                if (shouldDeselect)
                {
                    for (auto& b : balls) b.isChoosen = false;
                }
            }

            if (hitAny)
            {
                hitIt->isChoosen = true;
                isDragging = true;
                previousMouse = mouse;
            }
            else
            {
                isSelecting = true;
                selectionRect.x = mouse.x;
                selectionRect.y = mouse.y;
                selectionRect.width = 0;
                selectionRect.height = 0;
            }

            if (IsKeyDown(KEY_LEFT_ALT))
                balls.emplace_back(mouse, 5 + GetRandomValue(0, 39), randomColor());
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isSelecting = false;
            isDragging = false;
        }

        if (isDragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            Vector2 delta = Vector2Subtract(mouse, previousMouse);
            for (auto& b : balls)
            {
                if (b.isChoosen)
                    b.position = Vector2Add(b.position, delta);
            }
            previousMouse = mouse;
        }

        if (isSelecting)
        {
            selectionRect.width = mouse.x - selectionRect.x;
            selectionRect.height = mouse.y - selectionRect.y;

            Rectangle normRect = selectionRect;
            if (normRect.width < 0)
            {
                normRect.x += normRect.width;
                normRect.width = -normRect.width;
            }
            if (normRect.height < 0)
            {
                normRect.y += normRect.height;
                normRect.height = -normRect.height;
            }

            if (!IsKeyDown(KEY_LEFT_CONTROL))
            {
                for (auto& b : balls) b.isChoosen = false;
            }

            for (auto& b : balls)
            {
                if (b.position.x - b.radius >= normRect.x &&
                    b.position.x + b.radius <= normRect.x + normRect.width &&
                    b.position.y - b.radius >= normRect.y &&
                    b.position.y + b.radius <= normRect.y + normRect.height)
                {
                    b.isChoosen = true;
                }
            }
        }

        if (IsKeyPressed(KEY_DELETE))
        {
            for (auto it = balls.begin(); it != balls.end(); )
            {
                if (it->isChoosen) it = balls.erase(it);
                else ++it;
            }
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            for (auto& b : balls) if (b.isChoosen) b.color = randomColor();
        }

        if (!menu.isOpen)
        {
            if (IsKeyDown(KEY_LEFT_CONTROL))
            {
                if (IsKeyPressed(KEY_C))
                {
                    clipboard.clear();
                    Vector2 center = { 0, 0 };
                    int count = 0;
                    for (const auto& b : balls)
                    {
                        if (b.isChoosen)
                        {
                            clipboard.push_back(b);
                            center = Vector2Add(center, b.position);
                            count++;
                        }
                    }
                    if (count > 0) copyCenter = Vector2Scale(center, 1.0f / count);
                }
                else if (IsKeyPressed(KEY_X))
                {
                    clipboard.clear();
                    Vector2 center = { 0, 0 };
                    int count = 0;
                    for (const auto& b : balls)
                    {
                        if (b.isChoosen)
                        {
                            clipboard.push_back(b);
                            center = Vector2Add(center, b.position);
                            count++;
                        }
                    }
                    if (count > 0) copyCenter = Vector2Scale(center, 1.0f / count);
                    for (auto it = balls.begin(); it != balls.end(); )
                    {
                        if (it->isChoosen) it = balls.erase(it);
                        else ++it;
                    }
                }
                else if (IsKeyPressed(KEY_V))
                {
                    if (!clipboard.empty())
                    {
                        Vector2 pastePos = GetMousePosition();
                        Vector2 delta = Vector2Subtract(pastePos, copyCenter);
                        for (const auto& cb : clipboard)
                        {
                            balls.emplace_back(Vector2Add(cb.position, delta), cb.radius, cb.color);
                        }
                    }
                }
            }
        }

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            // Similar logic for right click
            bool hitAny = false;
            bool hitSelected = false;
            auto hitIt = balls.end();
            for (auto it = balls.begin(); it != balls.end(); ++it)
            {
                if (Vector2Distance(mouse, it->position) < it->radius)
                {
                    hitAny = true;
                    hitIt = it;
                    hitSelected = it->isChoosen;
                    break;
                }
            }

            if (!IsKeyDown(KEY_LEFT_CONTROL))
            {
                bool shouldDeselect = true;
                if (hitAny && hitSelected) shouldDeselect = false;
                if (shouldDeselect)
                {
                    for (auto& b : balls) b.isChoosen = false;
                }
            }

            if (hitAny)
            {
                hitIt->isChoosen = true;
            }

            menu.position = mouse;
            menu.isOpen = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& b : balls)
            b.draw();

        if (isSelecting)
        {
            Rectangle drawRect = selectionRect;

            if (drawRect.width < 0)
            {
                drawRect.x += drawRect.width;
                drawRect.width = -drawRect.width;
            }
            if (drawRect.height < 0)
            {
                drawRect.y += drawRect.height;
                drawRect.height = -drawRect.height;
            }

            DrawRectangleRec(drawRect, Color{150,150,240,50});
            DrawRectangleLinesEx(drawRect, 1, Color{200,200,255,255});
        }

        if (menu.isOpen)
        {
            Rectangle menuRect = { menu.position.x, menu.position.y, 150, (float)menu.items.size() * 20.f };
            DrawRectangleRec(menuRect, LIGHTGRAY);
            DrawRectangleLinesEx(menuRect, 1, DARKGRAY);

            if (CheckCollisionPointRec(mouse, menuRect))
            {
                int index = (int)((mouse.y - menu.position.y) / 20);
                if (index >= 0 && index < (int)menu.items.size())
                {
                    menu.hovered = index;
                    Rectangle hl = { menu.position.x, menu.position.y + (float)index * 20.f, 150, 20 };
                    DrawRectangleRec(hl, GRAY);
                }
            }

            for (size_t i = 0; i < menu.items.size(); ++i)
            {
                DrawText(menu.items[i].c_str(), (int)menu.position.x + 5, (int)menu.position.y + (int)i * 20, 15, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

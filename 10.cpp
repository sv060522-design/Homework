#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Ball {
    Vector2 pos;
    Vector2 vel;
    float mass;
    float charge;
    float r;
    Color color;
};

int main() {
    const int w = 800;
    const int h = 600;
    InitWindow(w, h, "Task 10");
    SetTargetFPS(60);
    float dt = 1.0f / 60.0f;

    std::srand(std::time(nullptr));

    std::vector<Ball> balls;
    int n = 5;
    for (int i = 0; i < n; ++i) {
        Ball b;
        b.r = 10.0f;
        b.pos.x = rand() % (w - 2 * (int)b.r) + b.r;
        b.pos.y = rand() % (h - 2 * (int)b.r) + b.r;
        b.vel = {0, 0};
        b.mass = 0.1f + static_cast<float>(rand()) / RAND_MAX * 0.4f;
        b.charge = -20.0f + static_cast<float>(rand()) / RAND_MAX * 40.0f;
        b.color = b.charge >= 0 ? RED : BLUE;
        balls.push_back(b);
    }

    float minDist = 30.0f;

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Ball b;
            b.r = 10.0f;
            b.pos = GetMousePosition();
            b.vel = {0, 0};
            b.mass = 0.05f;
            b.charge = -15.0f;
            b.color = BLUE;
            balls.push_back(b);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            Ball b;
            b.r = 10.0f;
            b.pos = GetMousePosition();
            b.vel = {0, 0};
            b.mass = 2.0f;
            b.charge = 20.0f;
            b.color = RED;
            balls.push_back(b);
        }

        std::vector<Vector2> forces(balls.size(), {0, 0});
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                Vector2 dir = { balls[j].pos.x - balls[i].pos.x, balls[j].pos.y - balls[i].pos.y };
                float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                if (dist < minDist) continue;
                float forceMag = - (balls[i].charge * balls[j].charge) / dist;
                Vector2 norm = { dir.x / dist, dir.y / dist };
                forces[i].x += forceMag * norm.x;
                forces[i].y += forceMag * norm.y;
                forces[j].x -= forceMag * norm.x;
                forces[j].y -= forceMag * norm.y;
            }
        }

        for (size_t i = 0; i < balls.size(); ++i) {
            Vector2 acc = { forces[i].x / balls[i].mass, forces[i].y / balls[i].mass };
            balls[i].vel.x += acc.x * dt;
            balls[i].vel.y += acc.y * dt;
            balls[i].pos.x += balls[i].vel.x * dt;
            balls[i].pos.y += balls[i].vel.y * dt;

            if (balls[i].pos.x < balls[i].r) {
                balls[i].pos.x = balls[i].r;
                balls[i].vel.x = -balls[i].vel.x;
            }
            if (balls[i].pos.x > w - balls[i].r) {
                balls[i].pos.x = w - balls[i].r;
                balls[i].vel.x = -balls[i].vel.x;
            }
            if (balls[i].pos.y < balls[i].r) {
                balls[i].pos.y = balls[i].r;
                balls[i].vel.y = -balls[i].vel.y;
            }
            if (balls[i].pos.y > h - balls[i].r) {
                balls[i].pos.y = h - balls[i].r;
                balls[i].vel.y = -balls[i].vel.y;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        for (const auto& b : balls) {
            DrawCircleV(b.pos, b.r, b.color);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <string>

struct Ball {
    Vector2 position;
    Vector2 velocity;
    float radius;
    float mass;
};

struct Polyline {
    std::vector<Vector2> points;
};

Vector2 ClosestPointOnSegment(Vector2 P, Vector2 A, Vector2 B) {
    Vector2 AB = Vector2Subtract(B, A);
    float lengthSqr = Vector2LengthSqr(AB);
    if (lengthSqr == 0.0f) return A;
    Vector2 AP = Vector2Subtract(P, A);
    float t = Vector2DotProduct(AP, AB) / lengthSqr;
    t = Clamp(t, 0.0f, 1.0f);
    return Vector2Add(A, Vector2Scale(AB, t));
}

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Task 11: Dark Theme");
    SetTargetFPS(60);

    std::vector<Ball> balls;
    std::vector<Polyline> polylines;
    std::vector<Vector2> current_polyline;
    bool gravityEnabled = false;
    float gravityValue = 980.0f;
    float decay = 1.0f;
    const int subSteps = 8;

    while (!WindowShouldClose()) {
        float frameTime = GetFrameTime();
        float dt = frameTime / subSteps;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                current_polyline.push_back(GetMousePosition());
            } else {
                Ball newBall;
                newBall.position = GetMousePosition();
                newBall.velocity.x = (float)GetRandomValue(-500, 500);
                newBall.velocity.y = (float)GetRandomValue(-500, 500);
                newBall.radius = 5.0f;
                newBall.mass = 1.0f;
                balls.push_back(newBall);
            }
        }

        if (IsKeyReleased(KEY_LEFT_CONTROL)) {
            if (current_polyline.size() > 1) {
                Polyline newPoly;
                newPoly.points = current_polyline;
                polylines.push_back(newPoly);
            }
            current_polyline.clear();
        }

        if (IsKeyPressed(KEY_G)) gravityEnabled = !gravityEnabled;

        if (IsKeyPressed(KEY_W)) {
            for (auto& b : balls) b.velocity = Vector2Scale(b.velocity, 1.2f);
        }
        if (IsKeyPressed(KEY_S)) {
            for (auto& b : balls) b.velocity = Vector2Scale(b.velocity, 0.8f);
        }

        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN)) {
            if (IsKeyPressed(KEY_UP)) decay += 0.01f;
            if (IsKeyPressed(KEY_DOWN)) decay -= 0.01f;
            decay = Clamp(decay, 0.0f, 1.0f);
        }

        if (IsKeyPressed(KEY_D) && !balls.empty()) balls.pop_back();
        if (IsKeyPressed(KEY_F) && !polylines.empty()) polylines.pop_back();
        if (IsKeyPressed(KEY_DELETE)) {
            balls.clear();
            polylines.clear();
            current_polyline.clear();
        }

        for (int step = 0; step < subSteps; ++step) {

            for (auto& ball : balls) {
                if (gravityEnabled) {
                    ball.velocity.y += gravityValue * dt;
                }
                ball.position = Vector2Add(ball.position, Vector2Scale(ball.velocity, dt));
            }

            for (auto& ball : balls) {
                if (ball.position.x - ball.radius < 0) {
                    ball.position.x = ball.radius;
                    if (ball.velocity.x < 0) ball.velocity.x = -ball.velocity.x * decay;
                }
                if (ball.position.x + ball.radius > screenWidth) {
                    ball.position.x = screenWidth - ball.radius;
                    if (ball.velocity.x > 0) ball.velocity.x = -ball.velocity.x * decay;
                }
                if (ball.position.y - ball.radius < 0) {
                    ball.position.y = ball.radius;
                    if (ball.velocity.y < 0) ball.velocity.y = -ball.velocity.y * decay;
                }
                if (ball.position.y + ball.radius > screenHeight) {
                    ball.position.y = screenHeight - ball.radius;
                    if (ball.velocity.y > 0) ball.velocity.y = -ball.velocity.y * decay;
                }
            }

            for (size_t i = 0; i < balls.size(); ++i) {
                for (size_t j = i + 1; j < balls.size(); ++j) {
                    Ball& b1 = balls[i];
                    Ball& b2 = balls[j];

                    Vector2 delta = Vector2Subtract(b2.position, b1.position);
                    float distSqr = Vector2LengthSqr(delta);
                    float minSqr = (b1.radius + b2.radius) * (b1.radius + b2.radius);

                    if (distSqr < minSqr && distSqr > 0.0f) {
                        float dist = sqrtf(distSqr);
                        Vector2 normal = Vector2Scale(delta, 1.0f / dist);

                        float overlap = (b1.radius + b2.radius - dist);
                        Vector2 separation = Vector2Scale(normal, overlap / 2.0f);
                        b1.position = Vector2Subtract(b1.position, separation);
                        b2.position = Vector2Add(b2.position, separation);

                        Vector2 relativeVel = Vector2Subtract(b2.velocity, b1.velocity);
                        float velAlongNormal = Vector2DotProduct(relativeVel, normal);

                        if (velAlongNormal < 0) {
                            float j_impulse = -(1.0f + decay) * velAlongNormal / 2.0f;
                            Vector2 impulseVec = Vector2Scale(normal, j_impulse);

                            b1.velocity = Vector2Subtract(b1.velocity, impulseVec);
                            b2.velocity = Vector2Add(b2.velocity, impulseVec);
                        }
                    }
                }
            }

            for (auto& ball : balls) {
                for (const auto& poly : polylines) {
                    for (size_t i = 0; i < poly.points.size() - 1; ++i) {
                        Vector2 p1 = poly.points[i];
                        Vector2 p2 = poly.points[i+1];

                        Vector2 closestPt = ClosestPointOnSegment(ball.position, p1, p2);
                        Vector2 delta = Vector2Subtract(ball.position, closestPt);
                        float dist = Vector2Length(delta);

                        if (dist < ball.radius) {
                            Vector2 normal = (dist > 0.0f) ? Vector2Scale(delta, 1.0f / dist) : Vector2{0, -1};

                            float overlap = ball.radius - dist;
                            ball.position = Vector2Add(ball.position, Vector2Scale(normal, overlap));

                            float velAlongNormal = Vector2DotProduct(ball.velocity, normal);
                            if (velAlongNormal < 0) {
                                Vector2 impulse = Vector2Scale(normal, (1.0f + decay) * velAlongNormal);
                                ball.velocity = Vector2Subtract(ball.velocity, impulse);
                            }
                        }
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& poly : polylines) {
            for (size_t i = 0; i < poly.points.size() - 1; ++i) {
                DrawLineEx(poly.points[i], poly.points[i+1], 1.5f, LIGHTGRAY);
            }
        }

        if (current_polyline.size() > 0) {
            for (size_t i = 0; i < current_polyline.size() - 1; ++i) {
                DrawLineEx(current_polyline[i], current_polyline[i+1], 1.5f, DARKGRAY);
            }
            if (IsKeyDown(KEY_LEFT_CONTROL)) {
                DrawLineEx(current_polyline.back(), GetMousePosition(), 1.0f, DARKGRAY);
            }
        }

        for (const auto& ball : balls) {
            DrawCircleV(ball.position, ball.radius, WHITE);
        }

        DrawText(TextFormat("Balls: %d | Polylines: %d", (int)balls.size(), (int)polylines.size()), 10, 10, 20, RAYWHITE);
        DrawText(TextFormat("Gravity (G): %s", gravityEnabled ? "ON" : "OFF"), 10, 35, 20, RAYWHITE);
        DrawText(TextFormat("Decay (Up/Down): %.2f", decay), 10, 60, 20, RAYWHITE);
        DrawText("Controls: LMB, LCtrl+LMB, W, S, D, F, Delete", 10, 85, 16, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
// Если вдруг не успею или забуду на коллоквиуме сдать, прошу хоть что-то за это поставить.
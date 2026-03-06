#include "raylib.h"
#include <vector>

class Toggle
{
private:
    Rectangle mTrack;
    bool mState;
    Color mOffColor;
    Color mOnColor;
    Color mKnobColor;
    float mKnobRadius;
    float mPadding;

public:
    Toggle(Vector2 position, float height)
    {
        mTrack = { position.x, position.y, height * 2.0f, height };
        mState = false;
        mOffColor = { 180, 180, 180, 255 };
        mOnColor = { 100, 200, 100, 255 };
        mKnobColor = WHITE;
        mKnobRadius = height * 0.4f;
        mPadding = height * 0.1f;
    }

    void handleEvents()
    {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, mTrack) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            mState = !mState;
        }
    }

    void draw() const
    {
        Color trackColor = mState ? mOnColor : mOffColor;
        float roundness = 0.5f;
        DrawRectangleRounded(mTrack, roundness, 0, trackColor);
        float centerY = mTrack.y + mTrack.height / 2;
        float centerX;
        if (mState)
        {
            centerX = mTrack.x + mTrack.width - mPadding - mKnobRadius;
        }
        else
        {
            centerX = mTrack.x + mPadding + mKnobRadius;
        }
        DrawCircle(centerX, centerY, mKnobRadius, mKnobColor);
    }

    bool getState() const { return mState; }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Toggle Switches");
    SetTargetFPS(60);

    const int count = 10;
    const float toggleHeight = 40.0f;
    const float toggleWidth = toggleHeight * 2.0f;
    const float spacing = 20.0f;
    const int cols = 5;
    std::vector<Toggle> toggles;

    for (int i = 0; i < count; ++i)
    {
        int row = i / cols;
        int col = i % cols;
        float x = spacing + col * (toggleWidth + spacing);
        float y = spacing + row * (toggleHeight + spacing);
        toggles.emplace_back(Vector2{x, y}, toggleHeight);
    }

    while (!WindowShouldClose())
    {
        if (IsWindowResized())
        {
            float newWidth = GetScreenWidth();
            float newHeight = GetScreenHeight();
            toggles.clear();
            for (int i = 0; i < count; ++i)
            {
                int row = i / cols;
                int col = i % cols;
                float x = spacing + col * (toggleWidth + spacing);
                float y = spacing + row * (toggleHeight + spacing);
                toggles.emplace_back(Vector2{x, y}, toggleHeight);
            }
        }

        for (auto& t : toggles)
        {
            t.handleEvents();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (const auto& t : toggles)
        {
            t.draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
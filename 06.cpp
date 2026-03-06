#include "raylib.h"
#include <algorithm>

class Slider
{
protected:
    Rectangle mTrackRect{};
    Rectangle mThumbRect{};

    bool mIsPressed{false};

public:
    Slider(Vector2 centerPosition, Vector2 trackSize, Vector2 thumbSize)
    {
        mTrackRect.width = trackSize.x;
        mTrackRect.height = trackSize.y;
        mTrackRect.x = centerPosition.x - trackSize.x / 2.0f;
        mTrackRect.y = centerPosition.y - trackSize.y / 2.0f;

        mThumbRect.width = thumbSize.x;
        mThumbRect.height = thumbSize.y;
        mThumbRect.x = centerPosition.x - thumbSize.x / 2.0f;
        mThumbRect.y = centerPosition.y - thumbSize.y / 2.0f;
    }

    void draw()
    {
        DrawRectangleRec(mTrackRect, {200, 200, 220, 255});
        DrawRectangleRec(mThumbRect, {150, 150, 240, 255});
    }

    void setRestrictedThumbPosition(Vector2 position)
    {
        float min = mTrackRect.x;
        float max = mTrackRect.x + mTrackRect.width;
        float clampedX = std::clamp(position.x, min, max);
        mThumbRect.x = clampedX - mThumbRect.width / 2.0f;
    }

    bool handleEvent()
    {
        Vector2 mousePosition = GetMousePosition();
        bool result = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, mThumbRect) ||
                CheckCollisionPointRec(mousePosition, mTrackRect))
            {
                mIsPressed = true;
                setRestrictedThumbPosition(mousePosition);
                result = true;
            }
        }

        if (mIsPressed && (GetMouseDelta().x != 0 || GetMouseDelta().y != 0))
        {
            setRestrictedThumbPosition(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            mIsPressed = false;
        }

        return result;
    }

    bool isPressed() const
    {
        return mIsPressed;
    }

    float getValue() const
    {
        float start = mTrackRect.x;
        float finish = mTrackRect.x + mTrackRect.width;
        float position = mThumbRect.x + mThumbRect.width / 2.0f;
        return 100.0f * (position - start) / (finish - start);
    }
};

int main()
{
    const int screenWidth = 900;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Three Sliders Color Circle");
    SetTargetFPS(60);

    float trackWidth = 300;
    float trackHeight = 8;
    float thumbWidth = 20;
    float thumbHeight = 20;
    float startX = 200;
    float startY = 150;
    float spacing = 100;

    Slider redSlider({startX, startY}, {trackWidth, trackHeight}, {thumbWidth, thumbHeight});
    Slider greenSlider({startX, startY + spacing}, {trackWidth, trackHeight}, {thumbWidth, thumbHeight});
    Slider blueSlider({startX, startY + 2 * spacing}, {trackWidth, trackHeight}, {thumbWidth, thumbHeight});

    float circleX = 650;
    float circleY = 300;
    float circleRadius = 120;

    while (!WindowShouldClose())
    {
        redSlider.handleEvent();
        greenSlider.handleEvent();
        blueSlider.handleEvent();

        float r = redSlider.getValue() * 2.55f;
        float g = greenSlider.getValue() * 2.55f;
        float b = blueSlider.getValue() * 2.55f;

        Color circleColor = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };

        BeginDrawing();
        ClearBackground(BLACK);

        redSlider.draw();
        greenSlider.draw();
        blueSlider.draw();

        DrawCircleV({circleX, circleY}, circleRadius, circleColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
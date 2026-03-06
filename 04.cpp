#include "raylib.h"
#include <string>
#include <iostream>

class Button
{
private:
    inline static const Color sDefaultColor{220, 220, 220, 255};
    inline static const Color sHoverColor{180, 200, 180, 255};
    inline static const Color sPressedColor{140, 160, 140, 255};

    Rectangle mRect;
    mutable Vector2 mTextPosition;
    std::string mText;
    int mFontSize;
    Color mCurrentColor;
    bool mIsPressed;

public:
    Button(Rectangle rect, int fontSize, const std::string& textData)
        : mRect(rect), mText(textData), mFontSize(fontSize)
    {
        int textWidth = MeasureText(mText.c_str(), mFontSize);
        mTextPosition.x = mRect.x + (mRect.width - textWidth) / 2.0f;
        mTextPosition.y = mRect.y + (mRect.height - mFontSize) / 2.0f;
        mCurrentColor = sDefaultColor;
        mIsPressed = false;
    }

    void draw() const
    {
        DrawRectangleRec(mRect, mCurrentColor);
        DrawText(mText.c_str(), (int)mTextPosition.x, (int)mTextPosition.y, mFontSize, BLACK);
    }

    bool handleEvent()
    {
        Vector2 mouse = GetMousePosition();
        bool hovered = CheckCollisionPointRec(mouse, mRect);

        if (!mIsPressed)
            mCurrentColor = hovered ? sHoverColor : sDefaultColor;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hovered)
        {
            mIsPressed = true;
            mCurrentColor = sPressedColor;
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            bool clicked = mIsPressed && hovered;
            mIsPressed = false;
            mCurrentColor = hovered ? sHoverColor : sDefaultColor;
            return clicked;
        }

        return false;
    }

    void setPosition(Vector2 pos)
    {
        mRect.x = pos.x;
        mRect.y = pos.y;
        int textWidth = MeasureText(mText.c_str(), mFontSize);
        mTextPosition.x = mRect.x + (mRect.width - textWidth) / 2.0f;
        mTextPosition.y = mRect.y + (mRect.height - mFontSize) / 2.0f;
    }
};

class BaseWindow
{
protected:
    static constexpr float dragAreaHeight = 30.0f;

    Rectangle mBaseRect{};
    Rectangle mDragRect{};

    bool mIsDragged{false};

    Vector2 mDragBaseDistance{};
    Vector2 mOffset{};

public:
    BaseWindow(Rectangle borders)
    {
        mDragRect = { borders.x, borders.y, borders.width, dragAreaHeight };
        mBaseRect = { borders.x, borders.y + dragAreaHeight, borders.width, borders.height - dragAreaHeight };

        mDragBaseDistance = {
            mDragRect.x - mBaseRect.x,
            mDragRect.y - mBaseRect.y
        };
    }

    virtual ~BaseWindow() = default;

    virtual bool onMousePressed(Vector2 mousePosition)
    {
        if (CheckCollisionPointRec(mousePosition, mDragRect))
        {
            mIsDragged = true;
            mOffset = {
                mousePosition.x - mDragRect.x,
                mousePosition.y - mDragRect.y
            };
        }
        return mIsDragged;
    }

    virtual void onMouseReleased()
    {
        mIsDragged = false;
    }

    virtual void onMouseMoved(Vector2 mousePosition)
    {
        if (mIsDragged)
        {
            mDragRect.x = mousePosition.x - mOffset.x;
            mDragRect.y = mousePosition.y - mOffset.y;

            mBaseRect.x = mDragRect.x - mDragBaseDistance.x;
            mBaseRect.y = mDragRect.y - mDragBaseDistance.y;
        }
    }

    virtual void handleEvents()
    {
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            onMousePressed(mousePosition);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            onMouseReleased();
        }

        if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0)
        {
            onMouseMoved(mousePosition);
        }
    }

    void setBaseColor(Color c) { }
    void setBaseSize(Vector2 sz) { mBaseRect.width = sz.x; mBaseRect.height = sz.y; }
    void setDragColor(Color c) { }
    void setDragSize(Vector2 sz) { mDragRect.width = sz.x; mDragRect.height = sz.y; }

    void setPosition(Vector2 p)
    {
        mBaseRect.x = p.x;
        mBaseRect.y = p.y;

        mDragRect.x = mBaseRect.x + mDragBaseDistance.x;
        mDragRect.y = mBaseRect.y + mDragBaseDistance.y;
    }

    virtual void draw(Color baseColor, Color dragColor) const
    {
        DrawRectangleRec(mBaseRect, baseColor);
        DrawRectangleRec(mDragRect, dragColor);
    }
};

class MessageWindow : public BaseWindow
{
protected:
    std::string mText;
    Color mBaseColor;
    Color mDragColor;

public:
    MessageWindow(Rectangle borders, const std::string& text, Color baseColor, Color dragColor)
        : BaseWindow(borders), mText(text), mBaseColor(baseColor), mDragColor(dragColor)
    {}

    void draw(Color baseColor, Color dragColor) const override
    {
        BaseWindow::draw(mBaseColor, mDragColor);
        DrawText(mText.c_str(), mBaseRect.x + 10, mBaseRect.y + 10, 20, BLACK);
    }
};

class ErrorWindow : public MessageWindow
{
public:
    ErrorWindow(Rectangle borders, const std::string& text)
        : MessageWindow(borders, text, RED, MAROON)
    {}
};

class DoneWindow : public MessageWindow
{
public:
    DoneWindow(Rectangle borders, const std::string& text)
        : MessageWindow(borders, text, GREEN, DARKGREEN)
    {}
};

class QuestionWindow : public BaseWindow
{
private:
    std::string mText;
    Button mOkButton;
    Button mCancelButton;

    void updateButtonPositions()
    {
        float buttonWidth = 80;
        float buttonHeight = 30;
        float spacing = 20;
        float totalWidth = 2 * buttonWidth + spacing;
        float startX = mBaseRect.x + (mBaseRect.width - totalWidth) / 2;
        float y = mBaseRect.y + mBaseRect.height - buttonHeight - 10;

        mOkButton.setPosition({ startX, y });
        mCancelButton.setPosition({ startX + buttonWidth + spacing, y });
    }

public:
    QuestionWindow(Rectangle borders, const std::string& text)
        : BaseWindow(borders), mText(text),
          mOkButton({0,0,80,30}, 20, "Ok"),
          mCancelButton({0,0,80,30}, 20, "Cancel")
    {
        updateButtonPositions();
    }

    void onMouseMoved(Vector2 mousePosition) override
    {
        BaseWindow::onMouseMoved(mousePosition);
        updateButtonPositions();
    }

    void handleEvents() override
    {
        BaseWindow::handleEvents();

        if (mOkButton.handleEvent())
        {
            std::cout << "Ok" << std::endl;
        }
        if (mCancelButton.handleEvent())
        {
            std::cout << "Cancel" << std::endl;
        }
    }

    void draw(Color baseColor, Color dragColor) const override
    {
        BaseWindow::draw(baseColor, dragColor);
        DrawText(mText.c_str(), mBaseRect.x + 10, mBaseRect.y + 10, 20, BLACK);
        mOkButton.draw();
        mCancelButton.draw();
    }
};

int main()
{
    InitWindow(800, 600, "Windows");
    SetTargetFPS(60);

    MessageWindow msg({100, 100, 300, 200}, "Hello", BLUE, LIGHTGRAY);
    ErrorWindow err({450, 100, 300, 200}, "Error!");
    DoneWindow done({100, 350, 300, 200}, "Success!");
    QuestionWindow q({450, 350, 300, 200}, "Are you sure?");

    while (!WindowShouldClose())
    {
        msg.handleEvents();
        err.handleEvents();
        done.handleEvents();
        q.handleEvents();

        BeginDrawing();
        ClearBackground(BLACK);

        msg.draw(WHITE, WHITE);
        err.draw(WHITE, WHITE);
        done.draw(WHITE, WHITE);
        q.draw(GRAY, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
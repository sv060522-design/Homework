#include "raylib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

class Observer
{
public:
    virtual void update(float value) = 0;
    virtual ~Observer() = default;
};

class Drawable
{
public:
    virtual void draw() const = 0;
    virtual ~Drawable() = default;
};

class Slider : public Drawable
{
private:
    Rectangle a;
    Rectangle b;
    Color c {200, 200, 220, 255};
    Color d {150, 150, 240, 255};
    bool e {false};
    std::set<Observer*> v;

public:
    Slider(Vector2 p, Vector2 s1, Vector2 s2)
    {
        a = {p.x - s1.x / 2, p.y - s1.y / 2, s1.x, s1.y};
        b = {p.x - s2.x / 2, p.y - s2.y / 2, s2.x, s2.y};
    }

    void draw() const override
    {
        DrawRectangleRec(a, c);
        DrawRectangleRec(b, d);
    }

    void updateInput()
    {
        Vector2 m = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(m, b) || CheckCollisionPointRec(m, a))
            {
                e = true;
                b.x = m.x - b.width / 2;
                notifyObservers();
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            e = false;
        }

        if (e)
        {
            float l = a.x;
            float r = a.x + a.width;
            float x = std::clamp(m.x, l, r);
            b.x = x - b.width / 2;
            notifyObservers();
        }
    }

    float getValue() const
    {
        float x = b.x + b.width / 2 - a.x;
        return x / a.width * 100.0f;
    }

    void addObserver(Observer* p)
    {
        v.insert(p);
    }

    void notifyObservers()
    {
        for (auto p : v)
        {
            p->update(getValue());
        }
    }
};

class Shape : public Drawable
{
public:
    virtual void setRotation(float value) = 0;
    virtual void setColor(float value) = 0;
};

class Circle : public Shape
{
private:
    Vector2 p;
    float r;
    float a {0.0f};
    Color c {0, 255, 0, 255};

public:
    Circle(Vector2 p, float r)
        : p(p), r(r)
    {
    }

    void draw() const override
    {
        DrawCircleV(p, r, c);

        float t = a * 3.14159265f / 180.0f;
        Vector2 q {p.x + r * cosf(t), p.y + r * sinf(t)};
        DrawLineEx(p, q, 4, BLACK);
    }

    void setRotation(float value) override
    {
        a = value * 3.6f;
    }

    void setColor(float value) override
    {
        c = {(unsigned char)(value * 2), 100, (unsigned char)(255 - value * 2), 255};
    }
};

class Square : public Shape
{
private:
    Vector2 p;
    float s;
    float a {0.0f};
    Color c {255, 0, 0, 255};

public:
    Square(Vector2 p, float s)
        : p(p), s(s)
    {
    }

    void draw() const override
    {
        DrawRectanglePro({p.x, p.y, s, s}, {s / 2, s / 2}, a, c);
    }

    void setRotation(float value) override
    {
        a = value * 3.6f;
    }

    void setColor(float value) override
    {
        c = {(unsigned char)(255 - value * 2), (unsigned char)(value * 2), 100, 255};
    }
};

class RotationObserver : public Observer
{
private:
    std::vector<Shape*>& v;

public:
    RotationObserver(std::vector<Shape*>& v)
        : v(v)
    {
    }

    void update(float value) override
    {
        for (auto p : v)
        {
            p->setRotation(value);
        }
    }
};

class ColorObserver : public Observer
{
private:
    std::vector<Shape*>& v;

public:
    ColorObserver(std::vector<Shape*>& v)
        : v(v)
    {
    }

    void update(float value) override
    {
        for (auto p : v)
        {
            p->setColor(value);
        }
    }
};

int main()
{
    InitWindow(800, 800, "Two Subjects");
    SetTargetFPS(60);

    Slider s1({400, 620}, {500, 20}, {25, 70});
    Slider s2({400, 720}, {500, 20}, {25, 70});

    std::vector<Shape*> v
    {
        new Circle({150, 300}, 60),
        new Square({400, 300}, 120),
        new Circle({650, 300}, 60)
    };

    RotationObserver r(v);
    ColorObserver c(v);

    s1.addObserver(&r);
    s2.addObserver(&c);

    while (!WindowShouldClose())
    {
        s1.updateInput();
        s2.updateInput();

        BeginDrawing();
        ClearBackground(BLACK);

        for (auto p : v)
        {
            p->draw();
        }

        s1.draw();
        s2.draw();

        DrawText("rotation", 130, 590, 24, WHITE);
        DrawText("color", 130, 690, 24, WHITE);

        EndDrawing();
    }

    for (auto p : v)
    {
        delete p;
    }

    CloseWindow();
    return 0;
}
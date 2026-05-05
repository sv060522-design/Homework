#include "raylib.h"
#include <vector>
#include "button.hpp"

float getRandomFloat(float min, float max)
{
    return GetRandomValue(0, 10000) / 10000.0f * (max - min) + min;
}

int getRandomInt(int min, int max)
{
    return GetRandomValue(min, max);
}

Color getRandomColor()
{
    return {
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        (unsigned char)GetRandomValue(0, 255),
        255
    };
}

struct Shape
{
    virtual void draw() = 0;
    virtual void rotate(float a) = 0;
    virtual void setPosition(Vector2 p) = 0;
    virtual Vector2 getPosition() = 0;
    virtual Vector2 getSize() = 0;
    virtual void setColor(Color c) = 0;
    virtual Color getColor() = 0;
    virtual ~Shape() = default;
};

class RectangleShape : public Shape
{
private:
    Vector2 mPosition;
    Vector2 mSize;
    float mRotation {0};
    Color mColor;

public:
    RectangleShape(Vector2 size) : mSize(size) {}

    void draw() override
    {
        DrawRectanglePro(
            {mPosition.x, mPosition.y, mSize.x, mSize.y},
            {mSize.x / 2, mSize.y / 2},
            mRotation,
            mColor
        );
    }

    void rotate(float a) override
    {
        mRotation += a;
    }

    void setPosition(Vector2 p) override
    {
        mPosition = p;
    }

    Vector2 getPosition() override
    {
        return mPosition;
    }

    Vector2 getSize() override
    {
        return mSize;
    }

    void setColor(Color c) override
    {
        mColor = c;
    }

    Color getColor() override
    {
        return mColor;
    }
};

class CircleShape : public Shape
{
private:
    Vector2 mPosition;
    float mRadius;
    float mRotation {0};
    Color mColor;
    int mSegments;

public:
    CircleShape(float r, int seg = 32) : mRadius(r), mSegments(seg) {}

    void draw() override
    {
        DrawPoly(mPosition, mSegments, mRadius, mRotation, mColor);
    }

    void rotate(float a) override
    {
        mRotation += a;
    }

    void setPosition(Vector2 p) override
    {
        mPosition = p;
    }

    Vector2 getPosition() override
    {
        return mPosition;
    }

    Vector2 getSize() override
    {
        return {mRadius * 2, mRadius * 2};
    }

    void setColor(Color c) override
    {
        mColor = c;
    }

    Color getColor() override
    {
        return mColor;
    }
};

class ShapePool
{
private:
    Rectangle mField;
    std::vector<Shape*> mShapes;

public:
    ShapePool(Vector2 position, Vector2 size)
    {
        mField = {position.x, position.y, size.x, size.y};
    }

    void addShape(Shape* p)
    {
        Vector2 size = p->getSize();

        Vector2 min = {size.x / 2, size.y / 2};
        Vector2 max = {
            mField.width - size.x / 2,
            mField.height - size.y / 2
        };

        Vector2 pos = {
            mField.x + getRandomFloat(min.x, max.x),
            mField.y + getRandomFloat(min.y, max.y)
        };

        p->setPosition(pos);
        p->setColor(getRandomColor());
        mShapes.push_back(p);
    }

    void addExisting(Shape* p)
    {
        mShapes.push_back(p);
    }

    Shape* removeLast()
    {
        if (mShapes.empty())
        {
            return nullptr;
        }

        Shape* p = mShapes.back();
        mShapes.pop_back();
        return p;
    }

    std::vector<Shape*> takeAll()
    {
        std::vector<Shape*> v = mShapes;
        mShapes.clear();
        return v;
    }

    void clear()
    {
        for (auto p : mShapes)
        {
            delete p;
        }

        mShapes.clear();
    }

    size_t getNumberOfShapes() const
    {
        return mShapes.size();
    }

    Vector2 getPosition() const
    {
        return {mField.x, mField.y};
    }

    Vector2 getSize() const
    {
        return {mField.width, mField.height};
    }

    Shape& getShape(size_t index)
    {
        return *mShapes.at(index);
    }

    void draw() const
    {
        DrawRectangleRec(mField, {0, 100, 200, 40});

        for (auto p : mShapes)
        {
            p->draw();
        }
    }

    ~ShapePool()
    {
        clear();
    }
};

class Command
{
public:
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual ~Command() = default;
};

class NoCommand : public Command
{
public:
    void execute() override
    {
    }

    void unexecute() override
    {
    }
};

class RotateCommand : public Command
{
private:
    ShapePool& mPool;
    size_t mIndex;
    float mAngle;
    std::vector<bool> mOk;

public:
    RotateCommand(ShapePool& pool, size_t index, float angle)
        : mPool(pool), mIndex(index), mAngle(angle)
    {
    }

    void execute() override
    {
        if (mIndex < mPool.getNumberOfShapes())
        {
            mPool.getShape(mIndex).rotate(mAngle);
            mOk.push_back(true);
        }
        else
        {
            mOk.push_back(false);
        }
    }

    void unexecute() override
    {
        if (mOk.empty())
        {
            return;
        }

        bool ok = mOk.back();
        mOk.pop_back();

        if (ok && mIndex < mPool.getNumberOfShapes())
        {
            mPool.getShape(mIndex).rotate(-mAngle);
        }
    }
};

class RandomColorCommand : public Command
{
private:
    ShapePool& mPool;
    size_t mIndex;
    std::vector<Color> mColors;
    std::vector<bool> mOk;

public:
    RandomColorCommand(ShapePool& pool, size_t index)
        : mPool(pool), mIndex(index)
    {
    }

    void execute() override
    {
        if (mIndex < mPool.getNumberOfShapes())
        {
            mColors.push_back(mPool.getShape(mIndex).getColor());
            mOk.push_back(true);
            mPool.getShape(mIndex).setColor(getRandomColor());
        }
        else
        {
            mOk.push_back(false);
        }
    }

    void unexecute() override
    {
        if (mOk.empty())
        {
            return;
        }

        bool ok = mOk.back();
        mOk.pop_back();

        if (ok && mIndex < mPool.getNumberOfShapes())
        {
            mPool.getShape(mIndex).setColor(mColors.back());
            mColors.pop_back();
        }
    }
};

class RandomAllColorsCommand : public Command
{
private:
    ShapePool& mPool;
    std::vector<std::vector<Color>> mColors;

public:
    RandomAllColorsCommand(ShapePool& pool) : mPool(pool) {}

    void execute() override
    {
        std::vector<Color> v;

        for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i)
        {
            v.push_back(mPool.getShape(i).getColor());
            mPool.getShape(i).setColor(getRandomColor());
        }

        mColors.push_back(v);
    }

    void unexecute() override
    {
        if (mColors.empty())
        {
            return;
        }

        std::vector<Color> v = mColors.back();
        mColors.pop_back();

        for (size_t i = 0; i < v.size() && i < mPool.getNumberOfShapes(); ++i)
        {
            mPool.getShape(i).setColor(v[i]);
        }
    }
};

class RandomAllPositionsCommand : public Command
{
private:
    ShapePool& mPool;
    std::vector<std::vector<Vector2>> mPositions;

public:
    RandomAllPositionsCommand(ShapePool& pool) : mPool(pool) {}

    void execute() override
    {
        std::vector<Vector2> v;

        for (size_t i = 0; i < mPool.getNumberOfShapes(); ++i)
        {
            Shape& shape = mPool.getShape(i);
            v.push_back(shape.getPosition());

            Vector2 size = shape.getSize();

            Vector2 min = {size.x / 2, size.y / 2};
            Vector2 max = {
                mPool.getSize().x - size.x / 2,
                mPool.getSize().y - size.y / 2
            };

            Vector2 pos = {
                mPool.getPosition().x + getRandomFloat(min.x, max.x),
                mPool.getPosition().y + getRandomFloat(min.y, max.y)
            };

            shape.setPosition(pos);
        }

        mPositions.push_back(v);
    }

    void unexecute() override
    {
        if (mPositions.empty())
        {
            return;
        }

        std::vector<Vector2> v = mPositions.back();
        mPositions.pop_back();

        for (size_t i = 0; i < v.size() && i < mPool.getNumberOfShapes(); ++i)
        {
            mPool.getShape(i).setPosition(v[i]);
        }
    }
};

class AddNewRandomShape : public Command
{
private:
    ShapePool& mPool;
    float mMinSize;
    float mMaxSize;
    std::vector<bool> mAdded;

public:
    AddNewRandomShape(ShapePool& pool, float minSize, float maxSize)
        : mPool(pool), mMinSize(minSize), mMaxSize(maxSize)
    {
    }

    void execute() override
    {
        int r = getRandomInt(0, 2);
        Shape* p;

        if (r == 0)
        {
            p = new RectangleShape({
                getRandomFloat(mMinSize, mMaxSize),
                getRandomFloat(mMinSize, mMaxSize)
            });
        }
        else if (r == 1)
        {
            p = new CircleShape(getRandomFloat(mMinSize / 2, mMaxSize / 2));
        }
        else
        {
            p = new CircleShape(getRandomFloat(mMinSize / 2, mMaxSize / 2), 3);
        }

        p->rotate(getRandomFloat(0, 360));
        mPool.addShape(p);
        mAdded.push_back(true);
    }

    void unexecute() override
    {
        if (mAdded.empty())
        {
            return;
        }

        mAdded.pop_back();

        Shape* p = mPool.removeLast();

        if (p != nullptr)
        {
            delete p;
        }
    }
};

class ClearCommand : public Command
{
private:
    ShapePool& mPool;
    std::vector<std::vector<Shape*>> mSaved;

public:
    ClearCommand(ShapePool& pool) : mPool(pool) {}

    void execute() override
    {
        mSaved.push_back(mPool.takeAll());
    }

    void unexecute() override
    {
        if (mSaved.empty())
        {
            return;
        }

        std::vector<Shape*> v = mSaved.back();
        mSaved.pop_back();

        for (auto p : v)
        {
            mPool.addExisting(p);
        }
    }

    ~ClearCommand()
    {
        for (auto& v : mSaved)
        {
            for (auto p : v)
            {
                delete p;
            }
        }
    }
};

class MultiCommand : public Command
{
private:
    std::vector<Command*> mCommands;

public:
    MultiCommand(std::vector<Command*> commands) : mCommands(commands) {}

    void execute() override
    {
        for (auto p : mCommands)
        {
            p->execute();
        }
    }

    void unexecute() override
    {
        for (int i = (int)mCommands.size() - 1; i >= 0; --i)
        {
            mCommands[i]->unexecute();
        }
    }

    ~MultiCommand()
    {
        for (auto p : mCommands)
        {
            delete p;
        }
    }
};

class ControlPanel
{
private:
    std::vector<Button*> mButtons;
    std::vector<Command*> mCommands;
    std::vector<Command*> mDone;
    Button* mUndoButton {nullptr};

public:
    void addButton(Button* p)
    {
        mButtons.push_back(p);
        mCommands.push_back(new NoCommand);
    }

    void addButton(Button* pb, Command* pc)
    {
        mButtons.push_back(pb);
        mCommands.push_back(pc);
    }

    void addUndoButton(Button* p)
    {
        mUndoButton = p;
    }

    void draw()
    {
        for (auto p : mButtons)
        {
            p->draw();
        }

        if (mUndoButton != nullptr)
        {
            mUndoButton->draw();
        }
    }

    void update()
    {
        for (size_t i = 0; i < mButtons.size(); ++i)
        {
            if (mButtons[i]->handle())
            {
                mCommands[i]->execute();
                mDone.push_back(mCommands[i]);
            }
        }

        if (mUndoButton != nullptr && mUndoButton->handle())
        {
            if (!mDone.empty())
            {
                Command* p = mDone.back();
                mDone.pop_back();
                p->unexecute();
            }
        }
    }

    ~ControlPanel()
    {
        for (auto p : mButtons)
        {
            delete p;
        }

        for (auto p : mCommands)
        {
            delete p;
        }

        delete mUndoButton;
    }
};

int main()
{
    InitWindow(800, 800, "Shapes and Command");
    SetTargetFPS(60);

    ShapePool pool({300, 50}, {450, 700});

    pool.addShape(new RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new RectangleShape({getRandomFloat(50, 150), getRandomFloat(50, 150)}));
    pool.addShape(new CircleShape(getRandomFloat(30, 100), 3));
    pool.addShape(new CircleShape(getRandomFloat(30, 100)));
    pool.addShape(new CircleShape(getRandomFloat(30, 100)));

    ControlPanel control;

    control.addButton(new Button({40, 80, 240, 40}, "Rotate First"), new RotateCommand(pool, 0, 30));
    control.addButton(new Button({40, 140, 240, 40}, "Rotate Second"), new RotateCommand(pool, 1, 45));
    control.addButton(new Button({40, 200, 240, 40}, "One Random Color"), new RandomColorCommand(pool, 3));
    control.addButton(new Button({40, 260, 240, 40}, "All Random Positions"), new RandomAllPositionsCommand(pool));
    control.addButton(new Button({40, 320, 240, 40}, "New Random Shape"), new AddNewRandomShape(pool, 10, 150));
    control.addButton(new Button({40, 380, 240, 40}, "All Random Colors"), new RandomAllColorsCommand(pool));
    control.addButton(new Button({40, 440, 240, 40}, "Clear"), new ClearCommand(pool));
    control.addButton(
        new Button({40, 500, 240, 40}, "All Random"),
        new MultiCommand({
            new RandomAllColorsCommand(pool),
            new RandomAllPositionsCommand(pool)
        })
    );

    control.addUndoButton(new Button({40, 700, 240, 40}, "Undo"));

    while (!WindowShouldClose())
    {
        control.update();

        BeginDrawing();
        ClearBackground(BLACK);

        pool.draw();
        control.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
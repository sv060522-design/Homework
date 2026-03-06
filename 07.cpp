#include "raylib.h"
#include <string>
#include <vector>

class DropList
{
private:
    Rectangle mRect;
    std::vector<std::string> mItems;
    int mSelected;
    bool mExpanded;
    int mItemHeight;

public:
    DropList(Vector2 position, float width, const std::vector<std::string>& items, int defaultSelected = 0)
        : mItems(items), mSelected(defaultSelected), mExpanded(false), mItemHeight(30)
    {
        mRect.x = position.x;
        mRect.y = position.y;
        mRect.width = width;
        mRect.height = mItemHeight;
    }

    void handleEvents()
    {
        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mouse, mRect))
            {
                mExpanded = !mExpanded;
            }
            else if (mExpanded)
            {
                bool clickedItem = false;
                for (size_t i = 0; i < mItems.size(); ++i)
                {
                    Rectangle itemRect = {
                        mRect.x,
                        mRect.y + (i + 1) * mItemHeight,
                        mRect.width,
                        (float)mItemHeight
                    };
                    if (CheckCollisionPointRec(mouse, itemRect))
                    {
                        mSelected = i;
                        mExpanded = false;
                        clickedItem = true;
                        break;
                    }
                }
                if (!clickedItem)
                {
                    mExpanded = false;
                }
            }
        }
    }

    void draw() const
    {
        DrawRectangleRec(mRect, SKYBLUE);
        DrawRectangleLinesEx(mRect, 2, DARKBLUE);
        DrawText(mItems[mSelected].c_str(), mRect.x + 10, mRect.y + 5, 20, BLACK);

        float arrowX = mRect.x + mRect.width - 20;
        float arrowY = mRect.y + mRect.height / 2;
        float arrowSize = 8;
        if (mExpanded)
        {
            DrawTriangle({arrowX, arrowY - arrowSize},
                         {arrowX - arrowSize, arrowY + arrowSize},
                         {arrowX + arrowSize, arrowY + arrowSize},
                         BLACK);
        }
        else
        {
            DrawTriangle({arrowX - arrowSize, arrowY - arrowSize},
                         {arrowX + arrowSize, arrowY - arrowSize},
                         {arrowX, arrowY + arrowSize},
                         BLACK);
        }

        if (mExpanded)
        {
            float totalHeight = mItems.size() * mItemHeight;
            Rectangle dropRect = { mRect.x, mRect.y + mItemHeight, mRect.width, totalHeight };
            DrawRectangleRec(dropRect, LIGHTGRAY);
            DrawRectangleLinesEx(dropRect, 2, DARKBLUE);

            for (size_t i = 0; i < mItems.size(); ++i)
            {
                Rectangle itemRect = {
                    mRect.x,
                    mRect.y + (i + 1) * mItemHeight,
                    mRect.width,
                    (float)mItemHeight
                };
                if (i == mSelected)
                {
                    DrawRectangleRec(itemRect, BLUE);
                }
                DrawText(mItems[i].c_str(), itemRect.x + 10, itemRect.y + 5, 20, BLACK);
            }
        }
    }

    int getSelected() const { return mSelected; }
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "DropList Example");
    SetTargetFPS(60);

    std::vector<std::string> items = {"Circle", "Square", "Triangle"};
    DropList dropList({300, 100}, 200, items);

    while (!WindowShouldClose())
    {
        dropList.handleEvents();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        dropList.draw();

        int selected = dropList.getSelected();
        Vector2 center = {400, 350};
        float radius = 80;

        if (selected == 0)
        {
            DrawCircleV(center, radius, RED);
        }
        else if (selected == 1)
        {
            Rectangle rect = {center.x - radius, center.y - radius, radius * 2, radius * 2};
            DrawRectangleRec(rect, GREEN);
        }
        else if (selected == 2)
        {
            Vector2 p1 = {center.x, center.y - radius};
            Vector2 p2 = {center.x - radius * 0.866f, center.y + radius * 0.5f};
            Vector2 p3 = {center.x + radius * 0.866f, center.y + radius * 0.5f};
            DrawTriangle(p1, p2, p3, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
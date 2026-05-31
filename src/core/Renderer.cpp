#include "AppState.hpp"
#include "Renderer.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <string>

void RenderAxis()
{
    DrawLineEx({20.0f, 35.0f}, {100.0f, 35.0f}, 2.0f, RED);
    DrawLineEx({20.0f, 35.0f}, {20.0f, 115.0f}, 2.0f, GREEN);
}

void RenderGrid()
{
    // https://github.com/raylib-extras/examples-c/blob/main/mouse_zoom/mouse_zoom.c
    // draw the 3d grid, rotated 90 degrees and centered around 0,0 just so we have something in the XY plane
    // DrawGrid関数だと色の変更はできない。
    rlPushMatrix();
    rlTranslatef(0, 25 * 50, 0);
    rlRotatef(90, 1, 0, 0);
    DrawGrid(100, 50);
    rlPopMatrix();
}

void Render(const Vector2 &mouse, const AppState &appState)
{
    RenderGrid();
    RenderAxis();

    Font font = GetFontDefault();
    // 点
    const auto &points = appState.GetPoints();
    for (int i = 0; i < points.size(); i++)
    {
        Color color = points[i].IsSelected() ? RED : BLACK;
        DrawCircle(points[i].X(), points[i].Y(), 4.0f, color);

        if (appState.IsPointNumberVisible())
        {
            Vector2 textLocation = Vector2{points[i].X() + 5.0f, points[i].Y() + 5.0f};
            std::string text = std::to_string(points[i].Id());
            DrawTextEx(font, text.c_str(), textLocation, 15.0f, 2.0f, BLACK);
        }
    }
}
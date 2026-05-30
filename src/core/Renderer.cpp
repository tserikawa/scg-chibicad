#include "AppState.hpp"
#include "Renderer.hpp"
#include "raylib-cpp.hpp"
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
        raylib::Color color = points[i].IsSelected() ? RED : BLACK;
        raylib::Vector2 point = Vector2{points[i].X(), points[i].Y()};
        point.DrawCircle(4.0f, color);

        if (appState.IsPointNumberVisible())
        {
            raylib::Vector2 textLocation = point.Add(Vector2{5.0f, 5.0f});
            std::string text = std::to_string(points[i].Id());
            raylib::DrawTextEx(font, text, textLocation, 15.0f, 2.0f, BLACK);
        }
    }
}
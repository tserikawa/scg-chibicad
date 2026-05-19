#include "AppState.hpp"
#include "Renderer.hpp"
#include "geometry/Point2f.hpp"
#include "raylib-cpp.hpp"
#include <string>

void Render(const Point2f &mouse, const AppState &appState)
{
    Font font = GetFontDefault();
    // 点
    const auto &points = appState.GetPoints();
    for (int i = 0; i < points.size(); i++)
    {
        raylib::Color color = points[i].IsSelected() ? RED : GRAY;
        raylib::Vector2 point = Vector2{points[i].X(), points[i].Y()};
        point.DrawCircle(4.0f, color);

        if (appState.IsPointNumberVisible())
        {
            raylib::Vector2 textLocation = point.Add(Vector2{5.0f, 5.0f});
            std::string text = std::to_string(points[i].Id());
            raylib::DrawTextEx(font, text, textLocation, 15.0f, 2.0f, WHITE);
        }
    }
}
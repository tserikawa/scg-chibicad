#include "ui/MenuBar.hpp"
#include "ui/ControlPanel.hpp"
#include "core/AppState.hpp"
#include "core/Renderer.hpp"

#include "raylib-cpp.hpp"
#include "rlImGui.h"
#include "imgui.h"

int main()
{
    raylib::Window window(1280, 720, "Geometry App");
    window.SetTargetFPS(60);

    // ImGui の初期化（raylib の InitWindow 後に呼ぶ）
    rlImGuiSetup(true);

    AppState appState;
    ControlPanel controlPanel("Info");
    Font font = GetFontDefault();

    SetExitKey(KEY_NULL);
    while (!window.ShouldClose())
    {
        // ウインドウ設定
        window.BeginDrawing();
        window.ClearBackground(raylib::Color(33, 33, 40));

        // イベント
        raylib::Vector2 rayMouse = GetMousePosition();
        bool isImGuiUseMouse = ImGui::GetIO().WantCaptureMouse;
        if (!isImGuiUseMouse)
        {
            if (raylib::Mouse::IsButtonPressed(MOUSE_BUTTON_LEFT))
            {
                appState.OnMouseLeftPressed(rayMouse.x, rayMouse.y);
            }
        }

        appState.OnPointNumberRenumber();
        Render(rayMouse, appState);

        // ImGui
        rlImGuiBegin();
        controlPanel.Draw(appState);
        DrawMenuBar(appState);
        rlImGuiEnd();

        if (raylib::Keyboard::IsKeyPressed(KEY_ESCAPE))
        {
            appState.OnEscapeKeyPressed();
        }

        if (appState.ShouldQuit())
        {
            break;
        }

        window.EndDrawing();
    }

    // ImGui の終了処理（CloseWindow 前に呼ぶ）
    rlImGuiShutdown();

    return 0;
}
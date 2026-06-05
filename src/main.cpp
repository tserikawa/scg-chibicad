#include "core/AppState.hpp"
#include "core/Renderer.hpp"
#include "ui/ControlPanel.hpp"
#include "ui/MenuBar.hpp"

#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

int main()
{
    InitWindow(1280, 720, "Geometry App");
    SetTargetFPS(60);

    // ImGui の初期化（raylib の InitWindow 後に呼ぶ）
    rlImGuiSetup(true);

    AppState appState;
    ControlPanel controlPanel("Info");
    Font font = GetFontDefault();

    SetExitKey(KEY_NULL);
    while (!WindowShouldClose())
    {
        // ウインドウ設定
        BeginDrawing();
        ClearBackground(Color{255, 255, 255});

        // マウス位置の取得
        Vector2 rayMouse = GetMousePosition();

        // イベント
        appState.InvokeMouseDraggingEvent(rayMouse.x, rayMouse.y);
        appState.InvokeEscapeKeyPressedEvent();
        appState.InvokeDeleteKeyPressedEvent();
        appState.InvokePoint2CollectionEvent();

        bool isImGuiUseMouse = ImGui::GetIO().WantCaptureMouse;
        if (!isImGuiUseMouse)
        {
            appState.InvokeMouseLeftPressedEvent(rayMouse.x, rayMouse.y);
        }

        // オブジェクトの表示
        Render(rayMouse, appState);

        // ImGui
        rlImGuiBegin();
        controlPanel.Draw(appState);
        DrawMenuBar(appState);
        rlImGuiEnd();

        if (appState.ShouldQuit())
        {
            break;
        }

        EndDrawing();
    }
    // ImGui の終了処理（CloseWindow 前に呼ぶ）
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
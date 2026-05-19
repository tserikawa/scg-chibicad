#include "MenuBar.hpp"
#include "imgui.h"

// MEMO:C++ではcpp内にのみ実装されている関数を区別する方法(命名規則など)はあるのか？

void DrawFileMenu(AppState &appState)
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New", "Cmd+N"))
        {
            appState.Reset();
        }
        if (ImGui::MenuItem("Open", "Cmd+O"))
        { /* 処理 */
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Quit", "Cmd+Q"))
        {
            appState.ChangeCommand(CommandState::Quit);
            appState.ChangeStatusMessage("Quit.");
        }
        ImGui::EndMenu();
    }
}

void DrawPointMenu(AppState &appState)
{
    if (ImGui::BeginMenu("Point"))
    {
        if (ImGui::MenuItem("Add", NULL))
        {
            appState.ChangeCommand(CommandState::AddPoint);
            appState.ChangeStatusMessage("Add Point.");
        }
        if (ImGui::MenuItem("Delete", NULL))
        {
            appState.ChangeCommand(CommandState::DeletePoint);
            appState.ChangeStatusMessage("Delete Point.");
        }
        if (ImGui::MenuItem("Select", NULL))
        {
            appState.ChangeCommand(CommandState::SelectPoint);
            appState.ChangeStatusMessage("Select Point.");
        }
        if (ImGui::BeginMenu("Renumber"))
        {
            if (ImGui::MenuItem("X /"))
            {
                appState.ChangeCommand(CommandState::RenumberPointByXAscending);
                appState.ChangeStatusMessage("Renumbered by coodinate x ascending.");
            }

            if (ImGui::MenuItem("X \\"))
            {
                appState.ChangeCommand(CommandState::RenumberPointByXDescending);
                appState.ChangeStatusMessage("Renumbered by coodinate x descending.");
            }

            if (ImGui::MenuItem("Y /"))
            {
                appState.ChangeCommand(CommandState::RenumberPointByYAscending);
                appState.ChangeStatusMessage("Renumbered by coodinate y ascending.");
            }

            if (ImGui::MenuItem("Y \\"))
            {
                appState.ChangeCommand(CommandState::RenumberPointByYDescending);
                appState.ChangeStatusMessage("Renumbered by coodinate y descending.");
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
}

void DrawLineMenu(AppState &appState)
{
    if (ImGui::BeginMenu("Line"))
    {
        if (ImGui::MenuItem("Add", NULL))
        {
        }
        if (ImGui::MenuItem("Delete", NULL))
        {
        }
        if (ImGui::MenuItem("Select", NULL))
        {
        }
        if (ImGui::MenuItem("Closest Point", NULL))
        {
        }
        ImGui::EndMenu();
    }
}

void DrawAlgorithmMenu(AppState &appState)
{
    if (ImGui::BeginMenu("Algorithm"))
    {
        if (ImGui::MenuItem("ConvexHull", NULL))
        {
        }
        ImGui::EndMenu();
    }
}

void DrawMenuBar(AppState &appState)
{
    if (ImGui::BeginMainMenuBar())
    {
        DrawFileMenu(appState);
        DrawPointMenu(appState);
        DrawLineMenu(appState);
        DrawAlgorithmMenu(appState);
        ImGui::EndMainMenuBar();
    }
}
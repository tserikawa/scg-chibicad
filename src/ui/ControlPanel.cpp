#include "ControlPanel.hpp"
#include "core/AppState.hpp"
#include "core/CommandState.hpp"
#include "imgui.h"

void ControlPanel::Draw(AppState &appState) const
{
    ImGui::SetNextWindowSize({300, 400}, ImGuiCond_Always);
    ImGui::Begin(m_name.c_str(), nullptr, ImGuiWindowFlags_NoResize);
    ImGui::SeparatorText("Current Command");
    ImGui::Text(GetCommandDisplayName(appState.GetCommand()).c_str());
    ImGui::SeparatorText("Message");
    ImGui::Text(appState.GetStatusMessage().c_str());
    ImGui::SeparatorText("Objects");
    ImGui::Text("Node Count: %d", appState.GetPointCount());
    ImGui::SeparatorText("Preview");
    ImGui::Checkbox("Number", &appState.PointNumberVisible());
    ImGui::SeparatorText("Info");

    ImGui::End();
}
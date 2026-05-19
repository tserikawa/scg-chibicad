#pragma once

#include "core/AppState.hpp"
#include <string>

class ControlPanel
{
    std::string m_name;

public:
    explicit ControlPanel(std::string name) : m_name(name) {};
    void Draw(AppState &appState) const;
};
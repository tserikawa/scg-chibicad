#pragma once

#include <string>

enum class CommandState
{
    Neautral,
    Quit,
    AddPoint,
    SelectPoint,
    UnSelectAllPoints,
    DeletePoint,
    RenumberPointByXAscending,
    RenumberPointByXDescending,
    RenumberPointByYAscending,
    RenumberPointByYDescending,
};

inline std::string GetCommandDisplayName(CommandState command) noexcept
{
    switch (command)
    {
    case CommandState::Neautral:
        return "Neautral";
    case CommandState::Quit:
        return "Quit";
    case CommandState::AddPoint:
        return "AddPoint";
    case CommandState::SelectPoint:
        return "SelectPoint";
    case CommandState::UnSelectAllPoints:
        return "UnSelectAllPoints";
    case CommandState::DeletePoint:
        return "DeletePoint";
    case CommandState::RenumberPointByXAscending:
        return "RenumberPointByXAscending";
    case CommandState::RenumberPointByXDescending:
        return "RenumberPointByXDescending";
    case CommandState::RenumberPointByYAscending:
        return "RenumberPointByYAscending";
    case CommandState::RenumberPointByYDescending:
        return "RenumberPointByYDescending";
    default:
        return "UnKnown";
    }
}
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
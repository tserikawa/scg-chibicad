#pragma once

#include <string>

enum class CommandState
{
    Neautral,
    Quit,
    AddPoint,
    SelectPoint,
    DeletePoint,
    RenumberPointByXAscending,
    RenumberPointByXDescending,
    RenumberPointByYAscending,
    RenumberPointByYDescending,
};
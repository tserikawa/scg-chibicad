#include "AppState.hpp"
#include "CommandState.hpp"
#include "collection/Point2Collection.hpp"
#include "geometry/Point2.hpp"
#include "raylib.h"
#include <algorithm>
#include <optional>
#include <vector>

AppState::AppState()
    : m_statusMessage("Waiting"),
      m_command(CommandState::Neautral),
      m_isPointNumberVisible(false),
      m_mousePressedLocation(std::nullopt)
{
}

void AppState::Reset() noexcept
{
    m_statusMessage = "Reset.";
    m_command = CommandState::Neautral;
    m_isPointNumberVisible = false;
    m_point2Collection.Clear();
}

void AppState::ChangeStatusMessage(const std::string message) noexcept
{
    m_statusMessage = message;
}

const std::string &AppState::GetStatusMessage() const noexcept
{
    return m_statusMessage;
}

bool AppState::ShouldQuit() const noexcept
{
    return m_command == CommandState::Quit;
}

void AppState::ChangeCommand(const CommandState command) noexcept
{
    m_command = command;
}

CommandState AppState::GetCommand() const noexcept
{
    return m_command;
}

int AppState::GetPointCount() const
{
    return m_point2Collection.Size();
}

const std::vector<ChibiCad::Point2> &AppState::GetPoints() const noexcept
{
    return m_point2Collection.GetAll();
}

bool &AppState::PointNumberVisible()
{
    return m_isPointNumberVisible;
}
bool AppState::IsPointNumberVisible() const noexcept
{
    return m_isPointNumberVisible;
}

const std::optional<SCG::Point2> &AppState::GetSelectRectangleStartPoint() const noexcept
{
    return m_mousePressedLocation;
}

void AppState::InvokeMouseLeftPressedEvent(float x, float y)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

    if (m_command == CommandState::AddPoint)
    {
        m_point2Collection.Add(x, y);
        return;
    }

    if (m_command == CommandState::SelectPoint)
    {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            m_point2Collection.UnSelect(x, y, ChibiCad::CoincidentEpsilon);
        }
        else
        {
            m_point2Collection.Select(x, y, ChibiCad::CoincidentEpsilon);
        }
        return;
    }

    if (m_command == CommandState::DeletePoint)
    {
        m_point2Collection.Remove(x, y, ChibiCad::CoincidentEpsilon);
        return;
    }
}

void AppState::InvokeEscapeKeyPressedEvent()
{
    if (!IsKeyPressed(KEY_ESCAPE))
    {
        return;
    }

    this->ChangeCommand(CommandState::Neautral);
    this->ChangeStatusMessage("Waiting");
}

void AppState::InvokeDeleteKeyPressedEvent()
{
    if (IsKeyPressed(KEY_DELETE))
    {
        m_point2Collection.RemoveSelected();
    }
}

void AppState::InvokePoint2CollectionEvent()
{

    if (this->GetCommand() == CommandState::UnSelectAllPoints)
    {
        m_point2Collection.UnSelectAll();
        this->ChangeCommand(CommandState::Neautral);
    }

    if (this->GetCommand() == CommandState::DeletePoint)
    {
        if (m_point2Collection.RemoveSelected())
        {
            this->ChangeStatusMessage("Selected points are deleted.");
        }
    }

    if (m_command == CommandState::RenumberPointByXAscending)
    {
        m_point2Collection.Renumber(ChibiCad::CompareXAscending);
        return;
    }

    if (m_command == CommandState::RenumberPointByXDescending)
    {
        m_point2Collection.Renumber(ChibiCad::CompareXDescending);
        return;
    }

    if (m_command == CommandState::RenumberPointByYAscending)
    {
        m_point2Collection.Renumber(ChibiCad::CompareYAscending);
        return;
    }

    if (m_command == CommandState::RenumberPointByYDescending)
    {
        m_point2Collection.Renumber(ChibiCad::CompareYDescending);
        return;
    }
}

void AppState::InvokeMouseDraggingEvent(float x, float y)
{
    if (m_command == CommandState::MovePoint)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !m_point2Collection.IsAnyPointDragging())
        {
            m_point2Collection.SetDraggingIndex(x, y, ChibiCad::CoincidentEpsilon);
        }

        if (m_point2Collection.IsAnyPointDragging())
        {
            m_point2Collection.UpdateDraggingPoint(x, y);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            m_point2Collection.ResetDraggingIndex();
        }
    }

    if (m_command == CommandState::SelectPoint)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !m_mousePressedLocation.has_value())
        {
            m_mousePressedLocation = SCG::Point2(x, y);
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (m_mousePressedLocation)
            {
                float minX = std::min(x, m_mousePressedLocation->X());
                float maxX = std::max(x, m_mousePressedLocation->X());
                float minY = std::min(y, m_mousePressedLocation->Y());
                float maxY = std::max(y, m_mousePressedLocation->Y());
                m_point2Collection.SelectByRectangle(minX, maxX, minY, maxY);
            }
            m_mousePressedLocation = std::nullopt;
        }
    }
}
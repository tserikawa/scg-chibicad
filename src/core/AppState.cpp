#include "AppState.hpp"
#include "CommandState.hpp"
#include "geometry/Point2.hpp"
#include "collection/Point2Collection.hpp"
#include <vector>

AppState::AppState()
{
    m_statusMessage = "Waiting";
    m_command = CommandState::Neautral;
    m_isPointNumberVisible = false;
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

void AppState::OnMouseLeftPressed(float x, float y)
{
    if (m_command == CommandState::AddPoint)
    {
        m_point2Collection.Add(x, y);
        return;
    }

    if (m_command == CommandState::SelectPoint)
    {
        m_point2Collection.Select(x, y, ChibiCad::CoincidentEpsilon);
        return;
    }

    if (m_command == CommandState::DeletePoint)
    {
        m_point2Collection.Remove(x, y, ChibiCad::CoincidentEpsilon);
        return;
    }
}

void AppState::OnEscapeKeyPressed()
{
    this->ChangeCommand(CommandState::Neautral);
    this->ChangeStatusMessage("Waiting");
}

void AppState::OnPointNumberRenumber()
{
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
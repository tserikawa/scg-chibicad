#include "AppState.hpp"
#include "geometry/Point2f.hpp"
#include "CommandState.hpp"
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
    m_pointCollection.Clear();
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
    return m_pointCollection.Size();
}

const std::vector<Point2f> &AppState::GetPoints() const noexcept
{
    return m_pointCollection.GetAll();
}

bool &AppState::PointNumberVisible()
{
    return m_isPointNumberVisible;
}
bool AppState::IsPointNumberVisible() const noexcept
{
    return m_isPointNumberVisible;
}

void AppState::OnMouseLeftPressed(const Point2f mouse)
{
    if (m_command == CommandState::AddPoint)
    {
        m_pointCollection.Add(mouse);
        return;
    }

    if (m_command == CommandState::SelectPoint)
    {
        m_pointCollection.Select(mouse);
        return;
    }

    if (m_command == CommandState::DeletePoint)
    {
        m_pointCollection.Delete(mouse);
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
        m_pointCollection.Renumber(CompareXAscending);
        return;
    }

    if (m_command == CommandState::RenumberPointByXDescending)
    {
        m_pointCollection.Renumber(CompareXDescending);
        return;
    }

    if (m_command == CommandState::RenumberPointByYAscending)
    {
        m_pointCollection.Renumber(CompareYAscending);
        return;
    }

    if (m_command == CommandState::RenumberPointByYDescending)
    {
        m_pointCollection.Renumber(CompareYDescending);
        return;
    }
}
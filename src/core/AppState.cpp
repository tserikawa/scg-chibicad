#include "AppState.hpp"
#include "command/AddPointCommand.hpp"
#include "command/DeletePointCommand.hpp"
#include "command/SelectPointCommand.hpp"
#include <memory>

AppState::AppState()
    : m_statusMessage("Waiting"),
      m_isPointNumberVisible(false),
      m_shouldQuit(false),
      m_mousePressedLocation(std::nullopt)
{
}

void AppState::Reset() noexcept
{
    m_statusMessage = "Reset.";
    m_isPointNumberVisible = false;
    m_shouldQuit = false;
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
    return m_shouldQuit;
}

void AppState::SetQuit()
{
    m_shouldQuit = true;
    m_statusMessage = "Quit.";
}

void AppState::SetAddPointMode()
{
    m_inputHandler.SetCommand(std::make_unique<ChibiCad::AddPointCommand>(m_point2Collection));
    m_statusMessage = "Add Point.";
}

void AppState::SetDeletePointMode()
{
    m_inputHandler.SetCommand(std::make_unique<ChibiCad::DeletePointCommand>(m_point2Collection));
    m_statusMessage = "Delete Point.";
}

void AppState::SetSelectPointMode()
{
    m_inputHandler.SetCommand(std::make_unique<ChibiCad::SelectPointCommand>(m_point2Collection));
    m_statusMessage = "Select Point.";
}

int AppState::GetPointCount() const
{
    return m_point2Collection.Size();
}

const std::vector<ChibiCad::Point2> &AppState::GetPoints() const noexcept
{
    return m_point2Collection.GetAll();
}

const std::optional<SCG::Point2> &AppState::GetSelectRectangleStartPoint() const noexcept
{
    return m_mousePressedLocation;
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
    m_inputHandler.OnMouseLeftClick(x, y);
}

void AppState::OnEscapeKeyPressed()
{
    m_statusMessage = "Waiting";
}
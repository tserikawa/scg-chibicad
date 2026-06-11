#pragma once

#include "collection/Point2Collection.hpp"
#include "handler/InputHandler.hpp"
#include "scg/geometry/Point2.hpp"
#include <optional>
#include <string>
#include <vector>

class AppState
{
  private:
    std::string m_statusMessage;
    ChibiCad::Point2Collection m_point2Collection;
    ChibiCad::InputHandler m_inputHandler;
    bool m_isPointNumberVisible;
    bool m_shouldQuit;
    std::optional<SCG::Point2> m_mousePressedLocation;

  public:
    explicit AppState();

    void Reset() noexcept;

    // ステータス
    void ChangeStatusMessage(const std::string message) noexcept;
    const std::string &GetStatusMessage() const noexcept;
    bool ShouldQuit() const noexcept;
    void SetQuit();

    // モード
    void SetAddPointMode();
    void SetDeletePointMode();
    void SetSelectPointMode();

    // 点
    int GetPointCount() const;
    const std::vector<ChibiCad::Point2> &GetPoints() const noexcept;
    const std::optional<SCG::Point2> &GetSelectRectangleStartPoint() const noexcept;

    // 表示状態
    bool &PointNumberVisible();
    bool IsPointNumberVisible() const noexcept;

    // イベント
    void OnMouseLeftPressed(float x, float y);
    void OnEscapeKeyPressed();
};
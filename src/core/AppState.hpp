#pragma once

#include "CommandState.hpp"
#include "collection/Point2Collection.hpp"
#include "geometry/Point2.hpp"
#include <optional>
#include <vector>

class AppState
{
    std::string m_statusMessage;
    CommandState m_command;
    ChibiCad::Point2Collection m_point2Collection;
    bool m_isPointNumberVisible;

    // マウス
    std::optional<SCG::Point2> m_mousePressedLocation;

  public:
    explicit AppState();

    void Reset() noexcept;

    // ステータス
    void ChangeStatusMessage(const std::string message) noexcept;
    const std::string &GetStatusMessage() const noexcept;
    bool ShouldQuit() const noexcept;

    // コマンド
    void ChangeCommand(const CommandState command) noexcept;
    CommandState GetCommand() const noexcept;

    // 点
    int GetPointCount() const;
    const std::vector<ChibiCad::Point2> &GetPoints() const noexcept;

    // 選択範囲を示す矩形の始点
    const std::optional<SCG::Point2> &GetSelectRectangleStartPoint() const noexcept;

    // 表示状態
    bool &PointNumberVisible();
    bool IsPointNumberVisible() const noexcept;

    // イベント
    void InvokeMouseLeftPressedEvent(float x, float y);
    void InvokeEscapeKeyPressedEvent();
    void InvokeDeleteKeyPressedEvent();
    void InvokePoint2CollectionEvent();
    void InvokeMouseDraggingEvent(float x, float y);
};
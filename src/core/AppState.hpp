#pragma once

#include "CommandState.hpp"
#include "geometry/Point2f.hpp"
#include "collection/PointCollection.hpp"
#include <vector>

class AppState
{
    std::string m_statusMessage;
    CommandState m_command;
    PointCollection m_pointCollection;
    bool m_isPointNumberVisible;

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
    const std::vector<Point2f> &GetPoints() const noexcept;

    // 表示状態
    bool &PointNumberVisible();
    bool IsPointNumberVisible() const noexcept;

    // イベント
    void OnMouseLeftPressed(const Point2f mouse);
    void OnEscapeKeyPressed();
    void OnPointNumberRenumber();
};
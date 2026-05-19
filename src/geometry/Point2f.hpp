#pragma once

#include <vector>
#include <string>

class Point2f
{
    int m_id;
    float m_x;
    float m_y;
    bool m_isSelected;

public:
    explicit Point2f(float x, float y)
        : m_id(-1), m_x(x), m_y(y), m_isSelected(false) {};
    explicit Point2f(int id, float x, float y)
        : m_id(id), m_x(x), m_y(y), m_isSelected(false) {};

    int Id() const noexcept;
    void ChangeId(int id) noexcept;
    float X() const noexcept;
    float Y() const noexcept;
    bool IsSelected() const noexcept;
    float DistanceTo(const Point2f &other) const noexcept;
    bool EpsilonEqual(const Point2f &other, float epsilon) const noexcept;

    void Select() noexcept;
    void UnSelect() noexcept;

    // const std::vector<std::string> &GetInfo() const noexcept;
};

bool CompareXAscending(const Point2f &lhs, const Point2f &rhs);
bool CompareXDescending(const Point2f &lhs, const Point2f &rhs);
bool CompareYAscending(const Point2f &lhs, const Point2f &rhs);
bool CompareYDescending(const Point2f &lhs, const Point2f &rhs);

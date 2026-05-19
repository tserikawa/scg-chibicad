#include "Point2f.hpp"
#include <cmath>
#include <vector>
#include <string>

int Point2f::Id() const noexcept
{
    return m_id;
}

void Point2f::ChangeId(int id) noexcept
{
    m_id = id;
}

float Point2f::X() const noexcept
{
    return m_x;
}

float Point2f::Y() const noexcept
{
    return m_y;
}

bool Point2f::IsSelected() const noexcept
{
    return m_isSelected;
}

float Point2f::DistanceTo(const Point2f &other) const noexcept
{
    float dx = m_x - other.m_x;
    float dy = m_y - other.m_y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Point2f::EpsilonEqual(const Point2f &other, float epsilon) const noexcept
{
    return this->DistanceTo(other) <= epsilon;
}

void Point2f::Select() noexcept
{
    m_isSelected = true;
}

void Point2f::UnSelect() noexcept
{
    m_isSelected = false;
}

bool CompareXAscending(const Point2f &lhs, const Point2f &rhs)
{
    return lhs.X() < rhs.X();
}

bool CompareXDescending(const Point2f &lhs, const Point2f &rhs)
{
    return lhs.X() > rhs.X();
}

bool CompareYAscending(const Point2f &lhs, const Point2f &rhs)
{
    return lhs.Y() < rhs.Y();
}

bool CompareYDescending(const Point2f &lhs, const Point2f &rhs)
{
    return lhs.Y() > rhs.Y();
}
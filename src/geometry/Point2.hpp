#pragma once

#include "scg/geometry/Point2.hpp"
#include "core/Constants.hpp"

namespace ChibiCad
{
    class Point2
    {
    private:
        int m_id;
        SCG::Point2 m_location;
        bool m_isSelected;

    public:
        Point2(int id, float x, float y)
            : m_id(id), m_location(SCG::Point2(x, y)), m_isSelected(false) {}

        bool operator==(const Point2 &other) const noexcept
        {
            return (m_id == other.Id()) && (m_location == other.Location());
        }

        bool operator!=(const Point2 &other) const noexcept
        {
            return !(*this == other);
        }

        SCG::Point2 Location() const noexcept
        {
            return m_location;
        }

        float X() const noexcept
        {
            return m_location.X();
        }

        float Y() const noexcept
        {
            return m_location.Y();
        }

        float DistanceTo(const Point2 &p) const noexcept
        {
            return m_location.DistanceTo(p.Location());
        }

        bool EpsilonEqual(const Point2 &other, float tolerance) const noexcept
        {
            return this->DistanceTo(other) <= tolerance;
        }

        bool EpsilonEqual(float x, float y, float tolerance) const noexcept
        {
            bool isSameX = abs(m_location.X() - x) <= tolerance;
            bool isSameY = abs(m_location.Y() - y) <= tolerance;
            return isSameX && isSameY;
        }

        int Id() const noexcept
        {
            return m_id;
        }

        void ChangeId(int newId) noexcept
        {
            m_id = newId;
        }

        bool IsSelected() const noexcept
        {
            return m_isSelected;
        }

        void Select() noexcept
        {
            m_isSelected = true;
        }

        void UnSelect() noexcept
        {
            m_isSelected = false;
        }
    };

    inline bool CompareXAscending(const Point2 &lhs, const Point2 &rhs)
    {
        return lhs.X() < rhs.X();
    }

    inline bool CompareXDescending(const Point2 &lhs, const Point2 &rhs)
    {
        return lhs.X() > rhs.X();
    }

    inline bool CompareYAscending(const Point2 &lhs, const Point2 &rhs)
    {
        return lhs.Y() < rhs.Y();
    }

    inline bool CompareYDescending(const Point2 &lhs, const Point2 &rhs)
    {
        return lhs.Y() > rhs.Y();
    }
}
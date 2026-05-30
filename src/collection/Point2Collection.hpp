#pragma once

#include "geometry/Point2.hpp"
#include <vector>
#include <optional>

namespace ChibiCad
{
    class Point2Collection
    {
    private:
        std::vector<Point2> m_points;
        int m_lastId;

    public:
        Point2Collection() : m_lastId(0) {};

        const Point2 &operator[](size_t i) const
        {
            return m_points[i];
        }

        void Add(float x, float y) noexcept
        {
            m_points.emplace_back(Point2(++m_lastId, x, y));
        }

        void Remove(float x, float y, float tolerance) noexcept
        {
            for (size_t i = 0; i < m_points.size(); i++)
            {
                if (m_points[i].EpsilonEqual(x, y, tolerance))
                {
                    m_points.erase(m_points.begin() + i);
                    return;
                }
            }
        }

        void Clear() noexcept
        {
            m_points.clear();
            m_lastId = 0;
        }

        std::optional<Point2> Get(int id) const noexcept
        {
            for (const auto &point : m_points)
            {
                if (point.Id() == id)
                {
                    return point;
                }
            }
            return std::nullopt;
        }

        const std::vector<Point2> &GetAll() const noexcept
        {
            return m_points;
        }

        int Size() const noexcept
        {
            return m_points.size();
        }

        void Select(float x, float y, float tolerance) noexcept
        {
            for (size_t i = 0; i < m_points.size(); i++)
            {
                if (m_points[i].EpsilonEqual(x, y, tolerance))
                {
                    m_points[i].Select();
                    return;
                }
            }
        }

        void UnSelect(float x, float y, float tolerance) noexcept
        {
            for (size_t i = 0; i < m_points.size(); i++)
            {
                if (m_points[i].EpsilonEqual(x, y, tolerance))
                {
                    m_points[i].UnSelect();
                    return;
                }
            }
        }

        template <typename Compare>
        void Renumber(Compare compare) noexcept
        {
            std::sort(m_points.begin(), m_points.end(), compare);

            for (size_t i = 0; i < m_points.size(); i++)
            {
                m_points[i].ChangeId(i + 1);
            }
            m_lastId = m_points.size();
        }
    };
}
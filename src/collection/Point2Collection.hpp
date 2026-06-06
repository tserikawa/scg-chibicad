#pragma once

#include "geometry/Point2.hpp"
#include <optional>
#include <vector>

namespace ChibiCad
{
    class Point2Collection
    {
      private:
        std::vector<Point2> m_points;
        int m_lastId;
        std::optional<size_t> m_draggingIndex;

      public:
        Point2Collection()
            : m_lastId(0),
              m_draggingIndex(std::nullopt) {};

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

        bool RemoveSelected() noexcept
        {
            bool isRemoved = false;
            std::vector<ChibiCad::Point2> newPoints;
            for (const auto &point : m_points)
            {
                if (!point.IsSelected())
                {
                    newPoints.emplace_back(point);
                    isRemoved = true;
                }
            }
            m_points = newPoints;
            return isRemoved;
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

        bool IsAnyPointDragging() const noexcept
        {
            return m_draggingIndex.has_value();
        }

        void SetDraggingIndex(float x, float y, float tolerance) noexcept
        {
            for (size_t i = 0; i < m_points.size(); i++)
            {
                if (m_points[i].EpsilonEqual(x, y, tolerance))
                {
                    m_draggingIndex = i;
                    return;
                }
            }
            m_draggingIndex = std::nullopt;
            return;
        }

        std::optional<size_t> GetDraggingIndex() const noexcept
        {
            return m_draggingIndex;
        }

        void UpdateDraggingPoint(float x, float y) noexcept
        {
            if (!m_draggingIndex.has_value())
            {
                return;
            }

            size_t index = m_draggingIndex.value();
            ChibiCad::Point2 point = m_points[index];
            m_points[index] = ChibiCad::Point2(point.Id(), x, y);
        }

        void ResetDraggingIndex() noexcept
        {
            m_draggingIndex = std::nullopt;
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

        void SelectByRectangle(float minX, float maxX, float minY, float maxY) noexcept
        {
            for (size_t i = 0; i < m_points.size(); i++)
            {
                if (minX <= m_points[i].X() && m_points[i].X() <= maxX && minY <= m_points[i].Y() &&
                    m_points[i].Y() <= maxY)
                {
                    m_points[i].Select();
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

        void UnSelectAll() noexcept
        {
            for (auto &point : m_points)
            {
                point.UnSelect();
            }
        }

        template <typename Compare> void Renumber(Compare compare) noexcept
        {
            std::sort(m_points.begin(), m_points.end(), compare);

            for (size_t i = 0; i < m_points.size(); i++)
            {
                m_points[i].ChangeId(i + 1);
            }
            m_lastId = m_points.size();
        }
    };
} // namespace ChibiCad
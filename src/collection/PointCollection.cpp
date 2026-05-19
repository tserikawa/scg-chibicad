#include "PointCollection.hpp"
#include "geometry/Point2f.hpp"
#include <algorithm>

void PointCollection::Add(const Point2f &point) noexcept
{
    m_points.emplace_back(Point2f(++m_lastId, point.X(), point.Y()));
}

void PointCollection::Delete(const Point2f &target) noexcept
{
    for (size_t i = 0; i < m_points.size(); i++)
    {
        if (m_points[i].EpsilonEqual(target, 5.0f))
        {
            m_points.erase(m_points.begin() + i);
            return;
        }
    }
}

void PointCollection::Select(const Point2f &target) noexcept
{
    for (auto &point : m_points)
    {
        if (point.EpsilonEqual(target, 5.0f))
        {
            point.Select();
            return;
        }
    }
}

const std::vector<Point2f> &PointCollection::GetAll() const noexcept
{
    return m_points;
}

void PointCollection::Clear() noexcept
{
    m_points.clear();
    m_lastId = 0;
}

int PointCollection::Size() const noexcept
{
    return m_points.size();
}

const Point2f &PointCollection::operator[](size_t index) const
{
    return m_points[index];
}
#pragma once

#include "geometry/Point2f.hpp"
#include <vector>
#include <algorithm>

class PointCollection
{
    std::vector<Point2f> m_points;
    int m_lastId;

public:
    PointCollection() : m_lastId(0) {};

    void Add(const Point2f &point) noexcept;
    void Delete(const Point2f &target) noexcept;
    void Select(const Point2f &target) noexcept;
    const std::vector<Point2f> &GetAll() const noexcept;
    void Clear() noexcept;

    int Size() const noexcept;

    const Point2f &operator[](size_t index) const;

    // MEMO:templateはC#やRustのように制約はいらない？コンパイル時に決定？

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
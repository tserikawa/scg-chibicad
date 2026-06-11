#pragma once

#include "IMouseCommand.hpp"
#include "collection/Point2Collection.hpp"
#include "core/Constants.hpp"

namespace ChibiCad
{
    class AddPointCommand : public IMouseCommand
    {
      private:
        Point2Collection &m_collection;
        float m_x;
        float m_y;

      public:
        AddPointCommand(Point2Collection &collection)
            : m_collection(collection)
        {
        }

        void Execute(float x, float y) override
        {
            m_x = x;
            m_y = y;
            m_collection.Add(m_x, m_y);
        }

        void Undo() override
        {
            m_collection.Remove(m_x, m_y, ChibiCad::CoincidentEpsilon);
        }
    };
} // namespace ChibiCad
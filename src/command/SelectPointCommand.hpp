#pragma once

#include "IMouseCommand.hpp"
#include "collection/Point2Collection.hpp"
#include "core/Constants.hpp"

namespace ChibiCad
{
    class SelectPointCommand : public IMouseCommand
    {
      private:
        Point2Collection &m_collection;
        float m_x;
        float m_y;

      public:
        SelectPointCommand(Point2Collection &collection)
            : m_collection(collection)
        {
        }

        void Execute(float x, float y) override
        {
            m_x = x;
            m_y = y;
            m_collection.Select(x, y, ChibiCad::CoincidentEpsilon);
        }

        void Undo() override
        {
            return;
        }
    };
} // namespace ChibiCad
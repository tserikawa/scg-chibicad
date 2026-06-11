#pragma once

namespace ChibiCad
{
    class IMouseCommand
    {
      public:
        virtual ~IMouseCommand() = default;
        virtual void Execute(float x, float y) = 0;
        virtual void Undo() = 0;
    };
} // namespace ChibiCad
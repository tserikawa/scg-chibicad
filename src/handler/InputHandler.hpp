#pragma once

#include "command/IMouseCommand.hpp"
#include <memory>

namespace ChibiCad
{
    class InputHandler
    {
        std::unique_ptr<IMouseCommand> m_command;

      public:
        void SetCommand(std::unique_ptr<IMouseCommand> command)
        {
            m_command = std::move(command);
        }

        void OnMouseLeftClick(float x, float y)
        {
            if (m_command)
            {
                m_command->Execute(x, y);
            }
        }
    };
} // namespace ChibiCad
#pragma once
#include <Controls.Trackbar.hpp>
#include "Handler.hpp"
namespace Gallery
{
    class Slider : public Controls::Trackbar
    {
    public:
        static inline Handler<HWND, void()> OnThumbPositionChangeHandlers;

        Slider(HWND parent, bool horizontal, int x, int y, int width, int height)
            : Controls::Trackbar{ parent,
            static_cast<DWORD>(horizontal ? Controls::Trackbar::Style::Horz : Controls::Trackbar::Style::Vert),
            x, y, width, height }
        {
        }

        template<typename Handler>
        void onPositionChange(Handler&& handler)
        {
            OnThumbPositionChangeHandlers.add(m_hwnd, std::forward<Handler>(handler));
        }

        void onPositionChange()
        {
            OnThumbPositionChangeHandlers.remove(m_hwnd);
        }

    };
}
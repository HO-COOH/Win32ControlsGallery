#pragma once
#include <Controls.Tooltip.hpp>
extern HWND gHwnd;
namespace Gallery::Pages::WindowPage
{

    class WindowStyleTooltip : public Controls::Tooltip
    {
    public:
        WindowStyleTooltip(HWND parent, DWORD style) :
            Controls::Tooltip{ parent, style }
        {

        }

    private:
        static inline HWND gItemTip{};

        static WindowStyleTooltip& GetInstance()
        {
            WindowStyleTooltip tooltip{ gHwnd, 0 };
            return tooltip;
        }
    public:
        static void OnResize(HWND hwnd, UINT state, int cx, int cy)
        {
            TOOLINFO info
            {
                .cbSize = sizeof(info) - sizeof(void*),
                .hwnd = hwnd,
                .uId = 0,
            };
            GetClientRect(hwnd, &info.rect);
            GetInstance().newToolRect(info);
        }

        static void UpdateTooltip(HWND hwnd, int x, int y)
        {
            gItemTip = GetInstance().hitTest(
                TTHITTESTINFO
                {
                    .hwnd = hwnd,
                    .pt = POINT{.x = x, .y = y}
                }
            ) ? hwnd : HWND{};
        }

        static void RelayEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            UpdateTooltip(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            GetInstance().relayEvent(
                MSG
                {
                    .hwnd = hwnd,
                    .message = msg,
                    .wParam = wParam,
                    .lParam = lParam
                }
            );
        }
    };

}
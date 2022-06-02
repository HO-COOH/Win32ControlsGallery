#pragma once
#include <pch.h>
#include "Handler.hpp"

namespace Gallery
{
    class ButtonEx : public Controls::Button
    {

    public:
        static inline Handler<HWND, void(HWND)> OnClickHandlers;
        ButtonEx(HWND parent, DWORD style, int x, int y, int width, int height)
            : Controls::Button(parent, style, x, y, width, height)
        {
        }

        ButtonEx(HWND parent, DWORD style)
            : Controls::Button(parent, style)
        {
        }

        template<typename Handler>
        void onClick(Handler&& handler)
        {
            OnClickHandlers.add(m_hwnd, std::move(handler));
        }

        void onClick()
        {
            OnClickHandlers.remove(m_hwnd);
        }
    };

    class CheckableButton : public ButtonEx
    {
        bool m_checked{};

        void addHandler()
        {
            OnClickHandlers.add(m_hwnd, [this](HWND hwnd)
                {
                    m_checked = !m_checked;
                    Button_SetCheck(hwnd, m_checked);
                });
        }
    public:
        CheckableButton(HWND parent, DWORD style, int x, int y, int width, int height)
			: ButtonEx(parent, style, x, y, width, height)
		{
			addHandler();
		}
		
        bool isChecked() const
        {
            return m_checked;
        }

        void setCheck(bool check)
        {
            OnClickHandlers.call(m_hwnd, m_hwnd);
        }

        void setCheckNoop(bool check)
        {
			m_checked = check;
			Button_SetCheck(m_hwnd, m_checked);
        }

        template<typename Handler>
        auto onClick(Handler&& handler)
        {
            OnClickHandlers.remove(m_hwnd);
            OnClickHandlers.add(m_hwnd, [handler, this](HWND hwnd) mutable
                {
                    m_checked = !m_checked;
                    Button_SetCheck(hwnd, m_checked);
                    handler(hwnd);
                });
        }

		template<typename Handler>
        auto newOnClick(Handler&& handler)
        {
            OnClickHandlers.remove(m_hwnd);
            OnClickHandlers.add(m_hwnd, std::forward<Handler>(handler));
        }
    };

    class RadioButton : public CheckableButton
    {
    public:
        RadioButton(HWND parent, LPCTSTR text, int x, int y, int width, int height)
            : CheckableButton(parent, static_cast<DWORD>(Controls::Button::Style::RadioButton), x, y, width, height)
        {
            setText(text);
        }
    };

    class Checkbox : public CheckableButton
    {
    public:

        Checkbox(HWND parent, LPCTSTR text, int x, int y, int width, int height)
            : CheckableButton(parent, static_cast<DWORD>(Controls::Button::Style::Checkbox), x, y, width, height)
        {
            setText(text);
        }
    };



    class Groupbox : public Controls::Button
    {
    public:
        Groupbox(HWND parent, LPCTSTR text)
            : Button(parent, static_cast<DWORD>(Controls::Button::Style::Groupbox))
        {
            setText(text);
        }

        Groupbox(HWND parent, LPCTSTR text, int x, int y, int width, int height)
            : Button(parent, static_cast<DWORD>(Controls::Button::Style::Groupbox), x, y, width, height)
        {
            setText(text);
        }
    };

}
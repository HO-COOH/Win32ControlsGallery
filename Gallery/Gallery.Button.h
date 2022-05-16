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

    class RadioButton : public ButtonEx
    {
    public:
        RadioButton(HWND parent, LPCTSTR text, int x, int y, int width, int height)
            : ButtonEx(parent, static_cast<DWORD>(Controls::Button::Style::RadioButton), x, y, width, height)
        {
            setText(text);
        }
    };

    class Checkbox : public ButtonEx
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
        Checkbox(HWND parent, LPCTSTR text)
            : ButtonEx(parent, static_cast<DWORD>(Controls::Button::Style::Checkbox))
        {
            setText(text);
            addHandler();
        }

        Checkbox(HWND parent, LPCTSTR text, int x, int y, int width, int height)
            : ButtonEx(parent, static_cast<DWORD>(Controls::Button::Style::Checkbox), x, y, width, height)
        {
            setText(text);
            addHandler();
        }

        bool isChecked() const
        {
            return m_checked;
        }

        void setCheck(bool check)
        {
            m_checked = check;
            ButtonEx::setCheck(check);
        }

        template<typename Handler>
        void onClick(Handler&& handler)
        {
            OnClickHandlers.remove(m_hwnd);
            OnClickHandlers.add(m_hwnd, [handler, this](HWND hwnd)
                {
                    m_checked = !m_checked;
                    Button_SetCheck(hwnd, m_checked);
                    handler(hwnd);
                });
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
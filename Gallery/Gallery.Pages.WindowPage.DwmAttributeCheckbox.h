#pragma once
#include "Gallery.Button.h"

extern HWND gCreatedWindow;
namespace Gallery::Pages::WindowPage
{
    template<typename ValueType>
    class DwmAttributeCheckbox : public Checkbox
    {
        DWORD const m_attribute{};
        ValueType const m_enableValue;
        ValueType const m_disableValue;
    public:
        DwmAttributeCheckbox(HWND parent, LPCTSTR text, int x, int y, int width, int height, DWORD attribute, ValueType enableValue, ValueType disableValue = {})
            : Checkbox(parent, text, x, y, width, height), m_attribute{ attribute }, m_enableValue{ enableValue }, m_disableValue{ disableValue }
        {
            onClick([this](HWND)
            {
                if (gCreatedWindow)
                {
                    DwmSetWindowAttribute(gCreatedWindow, m_attribute,
                        isChecked() ? &m_enableValue : &m_disableValue, sizeof(ValueType));
                }
            });
        }
    };
}

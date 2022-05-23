#pragma once
#include "Gallery.Button.h"
#include "Gallery.Pages.WindowPage.WindowStyleTooltip.h"
#include <ostream>
#include <future>

namespace Gallery::Pages::WindowPage
{
    class WindowStyleCheckbox : public Checkbox
    {
        DWORD m_style{};
        LPCTSTR m_text{};
        std::wstring m_description;
        WindowStyleTooltip m_tip;
        void addInfo();
    public:
        //WindowStyleCheckbox() :Checkbox(NULL, nullptr, 0, 0, 0, 0), m_tip{ NULL, {} } { assert(false); } JUST FOR DEBUG
        WindowStyleCheckbox(HWND parent, DWORD style, LPCTSTR text, int x, int y, int width, int height, LPCTSTR description);

        DWORD getValue() const;
        void flash(int times = 3);
        std::future<void> flashAsync(int times = 3);

        friend std::wostream& operator<<(std::wostream& os, WindowStyleCheckbox const& checkbox);
    };

}
#include "pch.h"
#include "Gallery.Pages.WindowPage.WindowStyleCheckbox.h"
#include <thread>

extern HWND gHwnd;

namespace Gallery::Pages::WindowPage
{
	void WindowStyleCheckbox::addInfo()
	{
        m_tip.setTitle(Controls::Tooltip::Icon::InfoLarge, m_text);
        TOOLINFO info
        {
            .cbSize = sizeof(info) - sizeof(void*),
            .uFlags = TTF_IDISHWND | TTF_SUBCLASS,
            .hwnd = gHwnd,
            .uId = reinterpret_cast<UINT_PTR>(m_hwnd),
            .hinst = gHinst,
            .lpszText = &m_description[0]
        };
        m_tip.addTool(info);
        m_tip.activate();
	}
	
    //WindowStyleCheckbox::WindowStyleCheckbox(HWND parent, DWORD style, LPCTSTR text, LPCTSTR description) : 
    //    Checkbox(parent, text), m_style{ style }, m_text{ text }, m_description{ description }, m_tip{ gHwnd, {} }
    //{
    //    addInfo();
    //}



    WindowStyleCheckbox::WindowStyleCheckbox(HWND parent, DWORD style, LPCTSTR text, int x, int y, int width, int height, LPCTSTR description) :
        Checkbox(parent, text, x, y, width, height), m_style{ style }, m_description{ description }, m_text{ text }, m_tip{ gHwnd, {} }
    {
        addInfo();
    }

    DWORD WindowStyleCheckbox::getValue() const
    {
        return isChecked() ? m_style : 0;
    }

    void WindowStyleCheckbox::flash(int times)
    {
        while (times--)
        {
            setCheck(true);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
            setCheck(false);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
        }
    }

    std::future<void> WindowStyleCheckbox::flashAsync(int times)
    {
        return std::async(
            std::launch::async,
            [this, times]() mutable
            {
                flash();
            }
        );
    }

	
    std::wostream& operator<<(std::wostream& os, WindowStyleCheckbox const& checkbox)
    {
        if (checkbox.isChecked())
            os << checkbox.m_text << L' ';
        return os;
    }

}
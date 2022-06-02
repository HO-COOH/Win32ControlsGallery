#include "pch.h"
#include "Gallery.Pages.WindowPage.ExampleWindow.h"
#include <WinUser.h>
#include <wingdi.h>

extern HINSTANCE gHinst;

namespace Gallery::Pages::WindowPage
{
    void ExampleWindow::Register()
    {
        static bool registered = false;
   	    
        if (registered)
            return;
		
        WNDCLASSEXW wcex{};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = ExampleWindow::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = gHinst;
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszClassName = className;
        wcex.hIconSm = NULL;
   		RegisterClassExW(&wcex);
   		registered = true;
    }
    void ExampleWindow::create(DWORD extendedStyle, DWORD style, std::wstringstream const& os)
    {
        Register();
        m_hwnd = CreateWindowEx(extendedStyle, className, os.str().c_str(),
        style, 1000, 1000, 800, 600, nullptr, nullptr, gHinst, nullptr);
    }
    ExampleWindow& ExampleWindow::operator=(HWND hwnd)
    {
        UI::Window::operator=(hwnd);
        return *this;
    }
    LRESULT ExampleWindow::OnNCCalcSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        //return 0;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    LRESULT ExampleWindow::OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        auto redBrush = CreateSolidBrush(RGB(255, 0, 0));

        FillRect(hdc, &ps.rcPaint, redBrush);

        EndPaint(hWnd, &ps);
        return {};
    }
	
	LRESULT ExampleWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
        switch (message)
        {
            case WM_NCCALCSIZE: return OnNCCalcSize(hWnd, message, wParam, lParam);
            case WM_PAINT:      return OnPaint(hWnd, message, wParam, lParam);
            //case WM_NCPAINT:
            //{
            //    HDC hdc;
            //    hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
            //    
            //    RECT rect{ .left = 0, .top = 0, .right = 1000, .bottom = 1000 };
            //    auto redBrush = CreateSolidBrush(RGB(255, 0, 0));


            //    FillRect(hdc, &rect, redBrush);
            //    // Paint into this DC 
            //    ReleaseDC(hWnd, hdc);
            //    return 0;
            //}
            default:            return DefWindowProc(hWnd, message, wParam, lParam);
        }
	}
}
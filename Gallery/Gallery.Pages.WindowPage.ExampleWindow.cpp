#include "pch.h"
#include "Gallery.Pages.WindowPage.ExampleWindow.h"
#include <WinUser.h>
#include <wingdi.h>

namespace Gallery::Pages::WindowPage
{
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
#include "pch.h"
#include "Gallery.SplashScreen.h"
#include <Uxtheme.h>
#include <dwmapi.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "dwmapi.lib")


extern HINSTANCE gHinst;

namespace Gallery
{

    static HBRUSH GetSystemColorBrush()
    {
        DWORD color{};
        BOOL _{};
        DwmGetColorizationColor(&color, &_);

        auto const r = (color & (0x00FF0000)) >> 16;
        auto const g = (color & (0x0000FF00)) >> 8;
        auto const b = color & (0x000000FF);

        OutputDebugString(L"here");

        return CreateSolidBrush(RGB(r, g, b));
    }
    static LRESULT OnWMPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);
        if (true)
        {
            auto image = SplashScreen::GetImageOf(hWnd);
            RECT rcClient{};
            GetClientRect(hWnd, &rcClient);
            FillRect(hdc, &rcClient, GetSystemColorBrush());
            auto const width = rcClient.right - rcClient.left;
            auto const height = rcClient.bottom - rcClient.top;
            rcClient.left = (width - 500) / 2;
            rcClient.right = rcClient.left + 500;
            rcClient.top = (height - 500) / 2;
            rcClient.bottom = rcClient.top + 500;
            FillRect(hdcMem, &rcClient, GetSystemColorBrush());
            auto memBitmap = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
            auto oldObj = SelectObject(hdcMem, memBitmap);
            image.render(hdcMem, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
            AlphaBlend(hdc, rcClient.left, rcClient.top, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hdcMem, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
                BLENDFUNCTION{
                    .BlendOp = AC_SRC_OVER,
                    .BlendFlags = 0,
                    .SourceConstantAlpha = 255,
                    .AlphaFormat = AC_SRC_ALPHA,
                });
            SelectObject(hdcMem, oldObj);
        }
        EndPaint(hWnd, &ps);
        return {};
    }

    static LRESULT OnWMCalcSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (wParam == TRUE)
            return 0;
        else
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    static LRESULT CALLBACK SplashWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            //case WM_NCCALCSIZE: return OnWMCalcSize(hWnd, message, wParam, lParam);	
            case WM_PAINT:      return OnWMPaint(hWnd, message, wParam, lParam);
            default:            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }



    void SplashScreen::Register()
    {
        static bool registered = false;
        if (registered)
            return;

        WNDCLASSEXW wcex{};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = SplashWndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = gHinst;
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszClassName = L"SplashScreen";
        RegisterClassExW(&wcex);
        registered = true;
    }

    SplashScreen::SplashScreen(int x, int y, int cx, int cy, int durationInMilliseconds)
    {
        Register();
        m_hwnd = CreateWindowEx(WS_EX_LAYERED, ClassName, ClassName, WS_POPUP | WS_CAPTION | WS_OVERLAPPEDWINDOW, x, y, cx, cy, NULL, NULL, gHinst, NULL);
    }

    void SplashScreen::show()
    {
        SetLayeredWindowAttributes(m_hwnd, 0, 255, LWA_ALPHA);
        InvalidateRect(m_hwnd, NULL, FALSE);

        m_splashThread = std::async(std::launch::async, [thisPtr = shared_from_this()]() mutable
        {
            ShowWindow(thisPtr->m_hwnd, SW_SHOW);
            short opacaity = 255;

            std::this_thread::sleep_for(std::chrono::seconds{ 3 });
            while (opacaity >= 0)
            {
                SetLayeredWindowAttributes(thisPtr->m_hwnd, 0, opacaity, LWA_ALPHA);
                std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
                opacaity -= 15;
                if (opacaity <= 200 && thisPtr->m_onFinish)
                    thisPtr->m_onFinish();
            }
            ShowWindow(thisPtr->m_hwnd, SW_HIDE);
            DestroyWindow(thisPtr->m_hwnd);
            thisPtr.reset();
        });
    }

    void SplashScreen::setImage(Graphics::Bitmap&& image)
    {
        m_image = std::move(image);
    }

    Graphics::Bitmap SplashScreen::GetImageOf(HWND hwnd)
    {
        return m_image;
    }
}

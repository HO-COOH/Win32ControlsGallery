#include "pch.h"
#include "Gallery.MainWindow.h"
#include "Resource.h"
#include "Gallery.Button.h"
#include "Gallery.Slider.h"
#include "Gallery.Tabs.h"
#include "Gallery.Spinbox.h"
#include <Util.System.hpp>

namespace Gallery
{
    WCHAR MainWindow::szWindowClass[MainWindow::MAX_LOADSTRING];
	
    void MainWindow::Register(HINSTANCE hInstance)
    {
        static bool registered = false;
        if (registered)
            return;
		
        LoadStringW(gHinst, IDC_CORE, szWindowClass, MAX_LOADSTRING);
		
        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = MainWindow::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CORE));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CORE);
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        RegisterClassExW(&wcex);
        registered = true;
    }
    HWND MainWindow::Create(LPCTSTR title, DWORD style, int x, int y, int cx, int cy, HWND parent, HMENU menu, HINSTANCE hInstance, LPVOID lpParam)
    {
        return CreateWindow(szWindowClass, title, style, x, y, cx, cy, parent, menu, hInstance, lpParam);
    }
    LRESULT MainWindow::OnCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        dpi = GetDpiForWindow(hWnd);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
        switch (message)
        {
            case WM_CREATE:     return OnCreate(hWnd, message, wParam, lParam);
            case WM_COMMAND:    return OnCommand(hWnd, message, wParam, lParam);
            case WM_PAINT:      return OnPaint(hWnd, message, wParam, lParam);
            case WM_DESTROY:    return OnDestroy(hWnd, message, wParam, lParam);
            case WM_HSCROLL:    return OnHScroll(hWnd, message, wParam, lParam);
            case WM_NOTIFY:     return OnNotify(hWnd, message, wParam, lParam);
            case WM_SIZE:       return OnSize(hWnd, message, wParam, lParam);
            case WM_SIZING:     return OnSizing(hWnd, message, wParam, lParam);
            case WM_DPICHANGED: return OnDpiChanged(hWnd, message, wParam, lParam);
            default:            return DefWindowProc(hWnd, message, wParam, lParam);
        }
	}

    LRESULT MainWindow::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        //switch(wPa)
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
            case IDM_ABOUT:
                DialogBox(gHinst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case Controls::Button::Message::Clicked:   ButtonEx::OnClickHandlers.call(HWND(lParam), HWND(lParam)); break;
            case Controls::Button::Message::Pushed:
                OutputDebugString(L"Button pushed");
                break;
            case Controls::Button::Message::HotItemChange:
                OutputDebugString(L"Button hot item change");
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return {};
    }

    LRESULT MainWindow::OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        [[maybe_unused]]HDC hdc = BeginPaint(hWnd, &ps);

        // TODO: Add any drawing code that uses hdc here...

        EndPaint(hWnd, &ps);
        return {};
    }

    LRESULT MainWindow::OnDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PostQuitMessage(0);
        return {};
    }

    LRESULT MainWindow::OnHScroll(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        auto const loWord = LOWORD(wParam);
        if (loWord == TB_THUMBTRACK || loWord == TB_LINEUP || loWord == TB_LINEDOWN || loWord == TB_PAGEUP || loWord == TB_PAGEDOWN)
        {
            Slider::OnThumbPositionChangeHandlers.call(HWND(lParam));
        }
        return {};
    }

    LRESULT MainWindow::OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        auto const param = reinterpret_cast<NMHDR*>(lParam);
        if (param)
        {
            switch (param->code)
            {
                case TCN_SELCHANGE: Tabs::OnSelectionChangeHandlers.call(param->hwndFrom, param); return {};
                case TRBN_THUMBPOSCHANGING: Slider::OnThumbPositionChangeHandlers.call(param->hwndFrom); return {};
                case UDN_DELTAPOS: return Spinbox::OnValueChangeHandlers.call(param->hwndFrom, reinterpret_cast<LPNMUPDOWN>(param));
                default:
                    break;
            }
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    LRESULT MainWindow::OnSize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        for (auto& handler : OnSizeHandler)
            handler();
        return {};
    }
    LRESULT MainWindow::OnSizing(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam)
    {
        return DefWindowProc(hwnd, message, wParam, lparam);
    }
    INT_PTR MainWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        // Message handler for about box.

        UNREFERENCED_PARAMETER(lParam);
        switch (message)
        {
            case WM_INITDIALOG:
                return (INT_PTR)TRUE;

            case WM_COMMAND:
                if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
                {
                    EndDialog(hDlg, LOWORD(wParam));
                    return (INT_PTR)TRUE;
                }
                break;
        }
        return (INT_PTR)FALSE;

    }

    static RECT GetParentRelativeWindowRect(HWND hwnd)
    {
        RECT rect{};
        GetWindowRect(hwnd, &rect);
        MapWindowRect(HWND_DESKTOP, GetAncestor(hwnd, GA_PARENT), &rect);
        return rect;
    };

    LRESULT MainWindow::OnDpiChanged(HWND hwnd, UINT message, WPARAM wparam, LPARAM lParam)
    {
        auto const dpiX = LOWORD(wparam);
        auto const dpiY = HIWORD(wparam);
        //auto& rect = *reinterpret_cast<RECT*>(lParam);


        //Handle font
        auto const logFont = Util::System::ParametersInfoForDpi<Util::System::Parameters::IconTitleLogFont>(dpiX);
        auto const newFont = CreateFontIndirect(&logFont);

        struct Info
        {
            HWND parent;
            HFONT font;
            WORD dpi;
        } info{ hwnd, newFont, dpiX };
        EnumChildWindows(hwnd, [](HWND hwnd, LPARAM lparam) -> BOOL
        {
            auto const& info = *reinterpret_cast<Info const*>(lparam);
            SendMessage(hwnd, WM_SETFONT, reinterpret_cast<LPARAM>(info.font), MAKELPARAM(TRUE, 0));
            
            RECT rect = GetParentRelativeWindowRect(hwnd);
            rect.left = MulDiv(rect.left, info.dpi, dpi);
            rect.right = MulDiv(rect.right, info.dpi, dpi);
            rect.top = MulDiv(rect.top, info.dpi, dpi);
            rect.bottom = MulDiv(rect.bottom, info.dpi, dpi);
            SetWindowPos(hwnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOZORDER);
            return TRUE;
        }, reinterpret_cast<LPARAM>(&info));

        dpi = dpiX;
        return {};
    }

    std::vector<std::function<void()>> MainWindow::OnSizeHandler;
}
#include "pch.h"
#include "Gallery.MainWindow.h"
#include "Resource.h"
#include "Gallery.Button.h"
#include "Gallery.Slider.h"

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
    LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
        switch (message)
        {
            case WM_COMMAND:    return OnCommand(hWnd, message, wParam, lParam);
            case WM_PAINT:      return OnPaint(hWnd, message, wParam, lParam);
            case WM_DESTROY:    return OnDestroy(hWnd, message, wParam, lParam);
            case WM_HSCROLL:    return OnHScroll(hWnd, message, wParam, lParam);
            case WM_NOTIFY:     return OnNotify(hWnd, message, wParam, lParam);
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
        HDC hdc = BeginPaint(hWnd, &ps);

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
        if (LOWORD(wParam) == TB_THUMBTRACK)
        {
            Slider::OnThumbPositionChangeHandlers.call(HWND(lParam));
        }
        return {};
    }

    LRESULT MainWindow::OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
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
}
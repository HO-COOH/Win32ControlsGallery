#pragma once
#include <vector>
#include <functional>
namespace Gallery
{
    class MainWindow
    {
        constexpr static auto MAX_LOADSTRING = 100;
		static WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
    public:
        static void Register(HINSTANCE hInstance);
        static HWND Create(LPCTSTR title, DWORD style, int x, int y, int cx, int cy, HWND parent, HMENU menu, HINSTANCE hInstance, LPVOID lpParam);
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnDestroy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnHScroll(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnNotify(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnSize(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnSizing(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);
        static INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

        static std::vector<std::function<void()>> OnSizeHandler;
    };

}
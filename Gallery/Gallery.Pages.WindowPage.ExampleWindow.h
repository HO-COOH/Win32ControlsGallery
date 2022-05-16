#pragma once
#include <windef.h>
namespace Gallery::Pages::WindowPage
{
	class ExampleWindow
	{
    public:
        static LRESULT OnNCCalcSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
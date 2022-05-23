#pragma once
#include <windef.h>
#include <UI.Window.hpp>

#include <sstream>
namespace Gallery::Pages::WindowPage
{
	class ExampleWindow : public UI::Window
	{
		static void Register();
		constexpr static inline auto className = L"WindowStyleTest";
    public:
		void create(DWORD extendedStyle, DWORD style, std::wstringstream const& os);
		ExampleWindow& operator=(HWND hwnd);
        static LRESULT OnNCCalcSize(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}
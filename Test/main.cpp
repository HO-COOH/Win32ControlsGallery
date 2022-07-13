#define _AFXDLL

#include <iostream>
#include <Flags.hpp>
#include <afxwin.h>
#include <Windows.h>
#include <Util.System.hpp>
#include <UI.Window.hpp>
#include <Controls.Button.hpp>
#include <UI.Dwm.hpp>
#include <UI.Gdi.hpp>
#pragma comment(lib, "dwmapi.lib")

constexpr static auto WindowClassName = L"Custom";

UINT dpi{};
HINSTANCE gHinst = GetModuleHandle(NULL);

template<typename T>
inline auto Scale(T value)
{
	return static_cast<int>(static_cast<float>(value) * dpi / 96);
}


//
//inline RECT GetFakeShadowRect(UI::Window& window)
//{
//	constexpr auto FakeShadowHeight = 
//	auto rect = window.getClientRect();
//	rect.bottom = rect.top + 
//}

enum class HoverButton
{
	None,
	Minimize,
	Maximize,
	Close
};

inline auto GetTitlebarRect(UI::Window& window, int titlebarHeight)
{
	constexpr auto TopAndBottomBorder = 2;

	CRect clientRect = window.getClientRect();
	clientRect.bottom = clientRect.top + Scale(titlebarHeight) + TopAndBottomBorder;
	return clientRect;
}

struct ButtonRects
{
	CRect close;
	CRect maximize;
	CRect minimize;

	ButtonRects(UI::Window& window, int buttonSize, CRect const& titlebarRect)
	{
		auto const buttonWidth = Scale(buttonSize);

		close = titlebarRect;
		close.left = close.right - buttonWidth;
		close.bottom = close.top + buttonWidth;
		close.OffsetRect(-2, (titlebarRect.Height() - buttonWidth) / 2);

		maximize = close;
		maximize.OffsetRect(-buttonWidth -2, 0);
		minimize = maximize;
		minimize.OffsetRect(-buttonWidth - 2, 0);
	}

};


UI::Window* gWindow;
Controls::Button* gMaximize;
Controls::Button* gMinimize;
Controls::Button* gClose;

namespace Windows2000
{
	namespace Colors
	{
		COLORREF const Background = RGB(0xd4, 0xd1, 0xc6);
		COLORREF const ButtonShadow = RGB(0x1c, 0x1f, 0x20);
	}
	
	namespace Brushes
	{
		CBrush Background{ Colors::Background };
		CBrush ButtonShadow{ Colors::ButtonShadow };
	}
}

namespace Windows10
{
	namespace Colors
	{
		COLORREF const Titlebar = RGB(150, 200, 180);
		COLORREF const ButtonFocus = RGB(33, 33, 33);
		COLORREF const ButtonUnfocus = RGB(127, 127, 127);
		COLORREF const ButtonHover = RGB(130, 180, 160);
		COLORREF const Shadow = RGB(100, 100, 100);
		COLORREF const Background = RGB(255,255,255);
	};

	namespace Brushes
	{
		CBrush TitlebarBrush{ Colors::Titlebar };
		CBrush ButtonHoverBrush{ Colors::ButtonHover };
		CBrush BackgroundBrush{ Colors::Background };
		CBrush ButtonFocusBrush{ Colors::ButtonFocus };
		CBrush ButtonUnfocusBrush{ Colors::ButtonUnfocus };
		CBrush CloseButtonHoverBrush{ RGB(0xCC, 0, 0) };
	};
	
	constexpr auto ButtonSize = 18;
	constexpr auto TitlebarHeight = 30;

	void Draw(UI::Window& window)
	{
		auto const hwnd = window.getHandle();
		auto const isActive = GetActiveWindow() == hwnd;

		PAINTSTRUCT ps;
		CDC hdc;
		hdc.Attach(BeginPaint(hwnd, &ps));

		//background
		hdc.FillRect(&ps.rcPaint, &Brushes::BackgroundBrush);

		//title bar background
		auto const titlebarRect = GetTitlebarRect(window, TitlebarHeight);
		TRIVERTEX vertices[]
		{
			TRIVERTEX{titlebarRect.left, titlebarRect.top, 0x0200, 0x2800, 0x6d00, 0},
			TRIVERTEX{titlebarRect.right, titlebarRect.bottom, 0xaa00, 0xc200, 0xd900, 0}
		};
		GRADIENT_RECT rect{ 0, 1 };
		hdc.GradientFill(vertices, 2, &rect, 1, GRADIENT_FILL_RECT_H);
		
		//buttons
		auto const rects = ButtonRects{ window, ButtonSize, titlebarRect };
		
		gMaximize->move(rects.maximize.left, rects.maximize.top);
		gMinimize->move(rects.minimize.left, rects.minimize.top);
		gClose->move(rects.close.left, rects.close.top);
		
		EndPaint(hwnd, &ps);
	}

	void OnDrawItem(HWND control, DRAWITEMSTRUCT* drawInfo)
	{
		if (drawInfo->CtlType != ODT_BUTTON || drawInfo->itemAction != ODA_DRAWENTIRE)
			return;

		auto const& rect = drawInfo->rcItem;
		CDC hdc;
		hdc.Attach(drawInfo->hDC);
		hdc.FillRect(&rect, &Windows2000::Brushes::Background);
		CRect bottomShadow = rect;
		bottomShadow.top = bottomShadow.bottom - 2;
		hdc.FillRect(bottomShadow, &Windows2000::Brushes::ButtonShadow);
		CRect topBright = rect;
		CBrush whiteBrush;
		whiteBrush.Attach(UI::Gdi::StockObject::Get<UI::Gdi::StockObject::WhiteBrush>());
		topBright.bottom = topBright.top + 2;
		hdc.FillRect(topBright, &whiteBrush);

		CPen pen{ static_cast<int>(UI::Gdi::Pen::Style::Solid), 3, Windows2000::Colors::ButtonShadow };
		hdc.SelectObject(&pen);
		if (gMinimize && drawInfo->hwndItem == gMinimize->getHandle())
		{
			hdc.MoveTo(rect.left + 4, rect.bottom - 5);
			hdc.LineTo(rect.right - 4, rect.bottom - 5);
		}
		else if(gMaximize && drawInfo->hwndItem == gMaximize->getHandle())
		{
			CRect smallerRect{ rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4 };
			hdc.Rectangle(smallerRect);
			hdc.MoveTo(smallerRect.left, smallerRect.top);
			hdc.LineTo(smallerRect.right, smallerRect.top);
		}
		else if (gClose && drawInfo->hwndItem == gClose->getHandle())
		{
			CRect smallerRect{ rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4 };
			hdc.MoveTo(smallerRect.left, smallerRect.top);
			hdc.LineTo(smallerRect.right, smallerRect.bottom);
			hdc.MoveTo(smallerRect.right, smallerRect.top);
			hdc.LineTo(smallerRect.left, smallerRect.bottom);
		}
	}
}


static LRESULT WindowProc(
	HWND handle,
	UINT message,
	WPARAM w_param,
	LPARAM l_param
)
{
	switch (message)
	{
		case WM_ACTIVATE: 
		{
			return DefWindowProc(handle, message, w_param, l_param);
		}
		case WM_CREATE: 
		{
			RECT size_rect;
			GetWindowRect(handle, &size_rect);

			SetWindowPos(
				handle, NULL,
				size_rect.left, size_rect.top,
				size_rect.right - size_rect.left, size_rect.bottom - size_rect.top,
				SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE
			);
			break;
		}
		case WM_NCCALCSIZE:
		{
			if (!w_param) return DefWindowProc(handle, message, w_param, l_param);
			dpi = GetDpiForWindow(handle);

			int frame_x = GetSystemMetricsForDpi(SM_CXFRAME, dpi);
			int frame_y = GetSystemMetricsForDpi(SM_CYFRAME, dpi);
			int padding = GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);

			NCCALCSIZE_PARAMS* params = (NCCALCSIZE_PARAMS*)l_param;
			RECT* requested_client_rect = params->rgrc;

			requested_client_rect->right -= frame_x + padding;
			requested_client_rect->left += frame_x + padding;
			requested_client_rect->bottom -= frame_y + padding;
			return 0;
		}
		case WM_PAINT:
			Windows10::Draw(*gWindow);
			break;
		case WM_DRAWITEM: Windows10::OnDrawItem(reinterpret_cast<HWND>(w_param), reinterpret_cast<DRAWITEMSTRUCT*>(l_param)); break;
	}
	return DefWindowProc(handle, message, w_param, l_param);
}

int main()
{
	Controls::Init();
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	WNDCLASSEXW const windowClass
	{
		.cbSize = sizeof(windowClass),
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WindowProc,
		.lpszClassName = WindowClassName,
	};
	RegisterClassEx(&windowClass);
	
	UI::Window window
	{
		WindowClassName, L"Custom window",
		Flags<DWORD>
		{
			UI::Window::Styles::ThickFrame,
			UI::Window::Styles::SysMenu,
			UI::Window::Styles::MaximizeBox,
			UI::Window::Styles::MinimizeBox,
			UI::Window::Styles::Visible
		},
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600
	};
	UI::Dwm::SetWindowAttribute(window, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND);
	gWindow = &window;

	window.show();

	auto const ButtonSize = Scale(Windows10::ButtonSize);
	Controls::Button minimize{ window, Flags<DWORD>{Controls::Button::Style::OwnerDraw},0,0,ButtonSize, ButtonSize };
	Controls::Button maximize{ window, Flags<DWORD>{Controls::Button::Style::OwnerDraw}, 0, 0, ButtonSize,ButtonSize };
	Controls::Button close{ window, Flags<DWORD>{Controls::Button::Style::OwnerDraw}, 0, 0, ButtonSize, ButtonSize };
	minimize.setText(L"-");
	maximize.setText(L"□");
	close.setText(L"X");

	RECT title_bar_rect = GetTitlebarRect(*gWindow, Windows10::TitlebarHeight);
	InvalidateRect(window, &title_bar_rect, FALSE);
	
	gMinimize = &minimize;
	gMaximize = &maximize;
	gClose = &close;


	for (MSG message = { 0 };;) 
	{
		BOOL result = GetMessageW(&message, 0, 0, 0);
		if (result > 0) 
		{
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
		else 
		{
			break;
		}
	}
}
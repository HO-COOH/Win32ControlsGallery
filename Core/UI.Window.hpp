#pragma once
#include <WinUser.h>
#include <wtypes.h>
namespace UI
{
	class Window
	{
	protected:
		HWND m_hwnd{};
	public:
		Window() = default;
		Window(HWND hwnd) : m_hwnd(hwnd) {}
		
		Window& operator=(HWND hwnd) { m_hwnd = hwnd; return *this; }
		operator bool() const { return m_hwnd != HWND{}; }
		operator HWND() const { return m_hwnd; }
		enum class ShowType
		{
			Hide = SW_HIDE,

			Normal = SW_NORMAL,				//activate and show window, if previously minimized or maximized, restore to its original size and position
			Show = SW_SHOW,					//activate and display its current size and position
			Restore = SW_RESTORE,			//same as <Normal>, but use when restoring a minimized window
			ShowDefault = SW_SHOWDEFAULT,	//use the value in STARTUPINFO

			ShowMinimized = SW_SHOWMINIMIZED,		//activate the window and show as minimized
			Minimize = SW_MINIMIZE,					//minimize the window and activate the next top-level window in Z order
			ShowMinNoActive = SW_SHOWMINNOACTIVE,	//minimize the window only, don't activate
			ForceMinimize = SW_FORCEMINIMIZE,		//minimize a window even if the thread that owns the window is not responding

			ShowMaximized = SW_SHOWMAXIMIZED,	//same as SW_MAXIMIZE
			Maximize = SW_MAXIMIZE,
			
			NoActive = SW_SHOWNOACTIVATE,
		};

		void show(ShowType showType)
		{
			ShowWindow(m_hwnd, static_cast<int>(showType));
		}

		void showAsync(ShowType showType)
		{
			ShowWindow(m_hwnd, static_cast<int>(showType));
		}

		void setStyle(DWORD style)
		{
			SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
		}

		void setHInstance()
		{

		}

		void setId()
		{

		}

		void setExtendedStyle(DWORD style)
		{
			SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, style);
		}

		void setUserData()
		{

		}

		void setWindowProcedure()
		{

		}

		void close()
		{
			CloseWindow(m_hwnd);
		}

		void update()
		{
			UpdateWindow(m_hwnd);
		}
	};
}
#pragma once
#include <WinUser.h>
#include <wtypes.h>
#include <Uxtheme.h>
#include <vsstyle.h>
#include <windowsx.h>
namespace UI
{
	class Window
	{
	protected:
		HWND m_hwnd{};
	public:

		//Constants
		enum class Styles : DWORD
		{
			Border = WS_BORDER,
			Caption = WS_CAPTION,
			Child = WS_CHILD,
			ChildWindow = WS_CHILDWINDOW,
			ClipChildren = WS_CLIPCHILDREN,
			ClipSiblings = WS_CLIPSIBLINGS,
			Disabled = WS_DISABLED,
			DlgFrame = WS_DLGFRAME,
			Group = WS_GROUP,
			HScroll = WS_HSCROLL,
			VScroll = WS_VSCROLL,
			Iconic = WS_ICONIC,
			Maximize = WS_MAXIMIZE,
			MaximizeBox = WS_MAXIMIZEBOX,
			Minimize = WS_MINIMIZE,
			MinimizeBox = WS_MINIMIZEBOX,
			Overlapped = WS_OVERLAPPED,
			OverlappedWindow = WS_OVERLAPPEDWINDOW,
			Popup = WS_POPUP,
			PopupWindow = WS_POPUPWINDOW,
			SizeBox = WS_SIZEBOX,
			SysMenu = WS_SYSMENU,
			TabStop = WS_TABSTOP,
			ThickFrame = WS_THICKFRAME,
			Tiled = WS_TILED,
			TiledWindow = WS_TILEDWINDOW,
			Visible = WS_VISIBLE,
		};

		enum class ExStyles : DWORD
		{
			AcceptFiles = WS_EX_ACCEPTFILES,
			AppWindow = WS_EX_APPWINDOW,
			ClientEdge = WS_EX_CLIENTEDGE,
			Composited = WS_EX_COMPOSITED,
			ContextHelp = WS_EX_CONTEXTHELP,
			ControlParent = WS_EX_CONTROLPARENT,
			DlgModalFrame = WS_EX_DLGMODALFRAME,
			Layered = WS_EX_LAYERED,
			LayoutRTL = WS_EX_LAYOUTRTL,
			Left = WS_EX_LEFT,
			LeftScrollBar = WS_EX_LEFTSCROLLBAR,
			LTRReading = WS_EX_LTRREADING,
			MDIChild = WS_EX_MDICHILD,
			NoActivate = WS_EX_NOACTIVATE,
			NoInheritLayout = WS_EX_NOINHERITLAYOUT,
			NoParentNotify = WS_EX_NOPARENTNOTIFY,
			NoRedirectionBitmap = WS_EX_NOREDIRECTIONBITMAP,
			OverlapppedWindow = WS_EX_OVERLAPPEDWINDOW,
			Right = WS_EX_RIGHT,
			RightScrollBar = WS_EX_RIGHTSCROLLBAR,
			RTLReading = WS_EX_RTLREADING,
			StaticEdge = WS_EX_STATICEDGE,
			ToolWindow = WS_EX_TOOLWINDOW,
			TopMost = WS_EX_TOPMOST,
			Transparent = WS_EX_TRANSPARENT,
			WindowEdge = WS_EX_WINDOWEDGE,
		};
		
		Window() = default;
		Window(HWND hwnd) : m_hwnd(hwnd) {}
		Window(LPCTSTR className, LPCTSTR windowName, DWORD style, int x, int y, int width, int height, HWND parent = {}, HMENU menu = {}, HINSTANCE instance = {}, LPVOID param = {}) :
			m_hwnd{ CreateWindow(className, windowName, style, x, y, width, height, parent, menu, instance, param) } {}
		Window(DWORD exStyle, LPCTSTR className, LPCTSTR windowName, DWORD style, int x, int y, int width, int height, HWND parent = {}, HMENU menu = {}, HINSTANCE instance = {}, LPVOID param = {}) :
			m_hwnd{ CreateWindowEx(exStyle, className, windowName, style, x, y, width, height, parent, menu, instance, param) } {}
		
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

		void show(ShowType showType = ShowType::Show)
		{
			ShowWindow(m_hwnd, static_cast<int>(showType));
		}

		void showAsync(ShowType showType)
		{
			ShowWindowAsync(m_hwnd, static_cast<int>(showType));
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

		HFONT getFont()
		{
			return GetWindowFont(m_hwnd);
		}

		void setExtendedStyle(DWORD style)
		{
			SetWindowLongPtr(m_hwnd, GWL_EXSTYLE, style);
		}

		template<typename T>
		LONG_PTR setUserData(T value)
		{
			static_assert(sizeof(T) <= sizeof(void*));
			return SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(value));
		}

		template<typename T>
		T getUserData() const
		{
			static_assert(sizeof(T) <= sizeof(void*));
			return reinterpret_cast<T>(GetWindowLongPtr(m_hwnd, GWLP_USERDATA));
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

		class Theme
		{
			HTHEME m_theme;
		public:
			struct PartsAndState
			{
				int part;
				int state;
			};
			Theme(HWND hwnd, LPCTSTR classList) : m_theme{ OpenThemeData(hwnd, classList) }
			{
			}
			SIZE getPartSize(PartsAndState partsAndState)
			{
				SIZE size{};
				GetThemePartSize(m_theme, NULL, partsAndState.part, partsAndState.state, NULL, TS_TRUE, &size);
				return size;
			}
			~Theme()
			{
				CloseThemeData(m_theme);
			}
		};

		struct Parts
		{
			class Caption
			{
				constexpr static auto id = WP_CAPTION;
			public:
				struct States
				{
					constexpr static auto Active = Theme::PartsAndState{Caption::id, CS_ACTIVE};
				};
			};
		};

		RECT getClientRect() const
		{
			RECT rect{};
			GetClientRect(m_hwnd, &rect);
			return rect;
		}

		Theme openThemeData()
		{
			return Theme{ m_hwnd, L"WINDOW" };
		}

		HWND getHandle() const { return m_hwnd; }
	};
}
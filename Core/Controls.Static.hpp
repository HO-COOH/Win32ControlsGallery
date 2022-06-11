#pragma once
#include "Controls.Control.hpp"
#include <windowsx.h>
namespace Controls
{
	class Static : public Control
	{
	public:
		//Constants
		constexpr static inline auto ClassName = WC_STATIC;

		Static(HWND parent, DWORD style, int x, int y, int width, int height)
		{
			m_hwnd = CreateWindowEx(
				0,
				ClassName,
				L"",
				style | WS_CHILD | WS_VISIBLE,
				x, y,
				width, height,
				parent,
				NULL,
				GetModuleHandle(NULL),
				NULL);
		}

		enum class Styles
		{
			Bitmap = SS_BITMAP,
			BlackFrame = SS_BLACKFRAME,
			BlackRect = SS_BLACKRECT,
			Center = SS_CENTER,
			CenterImage = SS_CENTERIMAGE,
			EditControl = SS_EDITCONTROL,
			EndEllipsis = SS_ENDELLIPSIS,
			EnhMetaFile = SS_ENHMETAFILE,
			EtchedFrame = SS_ETCHEDFRAME,
			EtchedHorz = SS_ETCHEDHORZ,
			EtchedVert = SS_ETCHEDVERT,
			GrayFrame = SS_GRAYFRAME,
			GrayRect = SS_GRAYRECT,
			Icon = SS_ICON,
			Left = SS_LEFT,
			LeftNoWordWrap = SS_LEFTNOWORDWRAP,
			NoPrefix = SS_NOPREFIX,
			Notify = SS_NOTIFY,
			OwnerDraw = SS_OWNERDRAW,
			PathEllipsis = SS_PATHELLIPSIS,
			RealSizeControl = SS_REALSIZECONTROL,
			RealSizeImage = SS_REALSIZEIMAGE,
			Right = SS_RIGHT,
			RightJust = SS_RIGHTJUST,
			Simple = SS_SIMPLE,
			Sunken = SS_SUNKEN,
			TypeMask = SS_TYPEMASK,
			WhiteFrame = SS_WHITEFRAME,
			WhiteRect = SS_WHITERECT,
			WordEllipsis = SS_WORDELLIPSIS
		};

		void enable(bool enable)
		{
			Static_Enable(m_hwnd, enable);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-static_geticon
		//wrong return type
		auto getIcon()
		{
			return reinterpret_cast<HICON>(sendMessage(STM_GETICON, 0, 0));
		}

		auto getText(LPTSTR buffer, int bufferSize)
		{
			Static_GetText(m_hwnd, buffer, bufferSize);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-static_gettextlength
		//wrong return type
		auto getTextLength()
		{
			return Static_GetTextLength(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-static_seticon
		//return previous icon
		auto setIcon(HICON icon)
		{
			return Static_SetIcon(m_hwnd, icon);
		}

		void setText(LPCTSTR buffer)
		{
			Static_SetText(m_hwnd, buffer);
		}
	};
}
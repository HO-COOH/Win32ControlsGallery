#pragma once
#include "Controls.Control.hpp"
namespace Controls
{
	class Trackbar : public Control
	{

	public:
		enum Style
		{
			AutoTicks = TBS_AUTOTICKS,
			Vert = TBS_VERT,
			Horz = TBS_HORZ,
			Top = TBS_TOP,
			Bottom = TBS_BOTTOM,
			Left = TBS_LEFT,
			Right = TBS_RIGHT,
			Both = TBS_BOTH,
			NoTicks = TBS_NOTICKS,
			EnableSelRange = TBS_ENABLESELRANGE,
			FixedLength = TBS_FIXEDLENGTH,
			NoThumb = TBS_NOTHUMB,
			ToolTips = TBS_TOOLTIPS,
			Reversed = TBS_REVERSED,
			DownIsLeft = TBS_DOWNISLEFT,
			NotifyBeforeMove = TBS_NOTIFYBEFOREMOVE,
			TransparentBkGnd = TBS_TRANSPARENTBKGND
		};

		inline Trackbar(HWND parent, DWORD style, int x, int y, int width, int height);

		//methods
		inline void setRange(int min, int max);
		inline int getPos();
		inline void setPos(bool redraw, int position);

		//Constants
		constexpr static auto ClassName = TRACKBAR_CLASS;
	};

	Trackbar::Trackbar(HWND parent, DWORD style, int x, int y, int width, int height)
	{
		m_hwnd = CreateWindowEx(
			0, ClassName, L"",
			WS_CHILD | WS_VISIBLE | style,
			x, y, width, height, parent,
			NULL, gHinst, NULL
		);
	}

	void Trackbar::setRange(int min, int max)
	{
		sendMessage(TBM_SETRANGE, TRUE, MAKEWPARAM(min, max));
	}

	int Trackbar::getPos()
	{
		return sendMessage(TBM_GETPOS, 0, 0);
	}

	void Trackbar::setPos(bool redraw, int position)
	{
		sendMessage(TBM_SETPOS, redraw, position);
	}
}
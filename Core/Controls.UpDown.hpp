#pragma once
#include "Controls.Control.hpp"
#include <cassert>

namespace Controls
{
	class UpDown : public Controls::Control
	{
	public:
		//Constants
		constexpr static inline auto ClassName = UPDOWN_CLASS;

		//Styles
		enum class Styles
		{
			AlignLeft = UDS_ALIGNLEFT,
			AlignRight = UDS_ALIGNRIGHT,
			ArrowKeys = UDS_ARROWKEYS,
			AutoBuddy = UDS_AUTOBUDDY,
			Horz = UDS_HORZ,
			HotTrack = UDS_HOTTRACK,
			NoThousands = UDS_NOTHOUSANDS,
			SetBuddyInt = UDS_SETBUDDYINT,
			Wrap = UDS_WRAP,
		};

		enum class Base
		{
			Decimal = 10,
			Hexadecimal = 16
		};
		
		inline UpDown(HWND parent, DWORD style, int x = 0, int y = 0, int width = 0, int height = 0, HWND buddy = NULL);

		//Methods
		auto getAccel(int numElements, UDACCEL* data)
		{
			return static_cast<int>(sendMessage(UDM_GETACCEL, numElements, reinterpret_cast<LPARAM>(data)));
		}

		auto setAccel(int numElements, UDACCEL* data)
		{
			return static_cast<BOOL>(sendMessage(UDM_SETACCEL, numElements, reinterpret_cast<LPARAM>(data)));
		}

		auto getBase()
		{
			return static_cast<Base>(sendMessage(UDM_GETBASE, 0, 0));
		}

		auto setBase(Base base)
		{
			return static_cast<Base>(sendMessage(UDM_SETBASE, static_cast<int>(base), 0));
		}

		auto getBuddy()
		{
			return reinterpret_cast<HWND>(sendMessage(UDM_GETBUDDY, 0, 0));
		}

		auto setBuddy(HWND buddy)
		{
			return reinterpret_cast<HWND>(sendMessage(UDM_SETBUDDY, reinterpret_cast<LPARAM>(buddy), 0));
		}
		
		auto getPos()
		{
			auto const pos = sendMessage(UDM_GETPOS, 0, 0);
			return LOWORD(pos);
		}

		auto getPos32(BOOL* result)
		{
			return static_cast<int>(sendMessage(UDM_GETPOS32, 0, reinterpret_cast<LPARAM>(result)));
		}

		auto setPos(short pos)
		{
			auto const previousPos = sendMessage(UDM_SETPOS, 0, MAKELPARAM(pos, 0));
			return LOWORD(previousPos);
		}

		auto setPos32(int pos)
		{
			return static_cast<int>(sendMessage(UDM_SETPOS32, 0, pos));
		}
		
		auto getRange()
		{
			auto const range = sendMessage(UDM_GETRANGE, 0, 0);
			return std::pair{ LOWORD(range), HIWORD(range) };
		}

		auto setRange(short minimum, short maximum)
		{
			assert(minimum <= UD_MAXVAL);
			assert(minimum >= UD_MINVAL);
			assert(maximum >= minimum);
			assert((maximum - minimum) <= UD_MAXVAL);
			sendMessage(UDM_SETRANGE, 0, MAKELPARAM(maximum, minimum));
		}

		void getRange32(int* minimum, int* maximum)
		{
			sendMessage(UDM_GETRANGE32, reinterpret_cast<WPARAM>(minimum), reinterpret_cast<LPARAM>(maximum));
		}

		void setRange32(int minimum, int maximum)
		{
			sendMessage(UDM_SETRANGE32, minimum, maximum);
		}

		auto getUnicodeFormat()
		{
			return sendMessage(UDM_GETUNICODEFORMAT, 0, 0);
		}

		auto setUnicodeFormat(bool useUnicode)
		{
			return sendMessage(UDM_SETUNICODEFORMAT, useUnicode, 0);
		}
	};

	UpDown::UpDown(HWND parent, DWORD style, int x, int y, int width, int height, HWND buddy)
	{
		m_hwnd = CreateWindowEx(
			0,
			ClassName,
			NULL,
			WS_CHILD | style | WS_VISIBLE,
			x, y,
			width, height,
			parent,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);
		if (buddy)
			setBuddy(buddy);
	}
}
#pragma once
#include "Util.Error.hpp"
#include "UI.hpp"
#include <dwmapi.h>

namespace UI::Dwm
{
	template<typename ValueType>
	void SetWindowAttribute(HWND hwnd, DWMWINDOWATTRIBUTE attribute, ValueType value)
	{
		CheckRet(DwmSetWindowAttribute(hwnd, attribute, &value, sizeof(value)));
	}

	template<typename ValueType>
	auto GetWindowAttribute(HWND hwnd, DWMWINDOWATTRIBUTE attribute)
	{
		ValueType value;
		CheckRet(DwmGetWindowAttribute(hwnd, attribute, &value, sizeof(value)), value);
	}

	inline auto GetColorizationColor()
	{
		DWORD color{};
		BOOL _{};
		CheckRet(DwmGetColorizationColor(&color, &_));
		return Color
		{
			.r = static_cast<BYTE>((color & (0x00FF0000)) >> 16),
			.g = static_cast<BYTE>((color & (0x0000FF00)) >> 8),
			.b = static_cast<BYTE>(color & 0x000000FF),
			.a = static_cast<BYTE>((color & (0xFF000000)) >> 24)
		};
	}

	inline auto GetColorizationColor(BOOL& opaque)
	{
		DWORD color{};
		CheckRet(DwmGetColorizationColor(&color, &opaque));
		return Color
		{
			.r = static_cast<BYTE>((color & (0x00FF0000)) >> 16),
			.g = static_cast<BYTE>((color & (0x0000FF00)) >> 8),
			.b = static_cast<BYTE>(color & 0x000000FF),
			.a = static_cast<BYTE>((color & (0xFF000000)) >> 24)
		};
	}
}
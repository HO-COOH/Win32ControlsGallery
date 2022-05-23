#pragma once
#include "Util.Error.hpp"
#include "UI.hpp"
#include <dwmapi.h>
#include "Util.System.hpp"
#include <cassert>

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

	struct ColorizationColor : public Color
	{
		BOOL opaque;
	};

	inline auto GetColorizationColor()
	{
		DWORD color{};
		BOOL opaque{};
		CheckRet(DwmGetColorizationColor(&color, &opaque));
		return ColorizationColor
		{
			static_cast<BYTE>((color & (0x00FF0000)) >> 16),
			static_cast<BYTE>((color & (0x0000FF00)) >> 8),
			static_cast<BYTE>(color & 0x000000FF),
			static_cast<BYTE>((color & (0xFF000000)) >> 24),
			opaque
		};
	}

	inline void EnableBlurBehindWindow(HWND hwnd, DWM_BLURBEHIND const& blurData)
	{
		CheckRet(DwmEnableBlurBehindWindow(hwnd, &blurData));
	}

	inline void EnableComposition()
	{
		//assert(!IsWindowsVersion8OrGreater());
		#pragma warning(disable: 4995)
		CheckRet(DwmEnableComposition(DWM_EC_ENABLECOMPOSITION));
	}

	inline void DisableComposition()
	{
		//assert(!IsWindowsVersion8OrGreater());
		#pragma warning(disable: 4995)
		CheckRet(DwmEnableComposition(DWM_EC_DISABLECOMPOSITION));
	}
}
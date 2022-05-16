#pragma once
#include "Util.Error.hpp"
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
		CheckRet(DwmGetWindowAttribute(hwnd, attribute, &value, sizeof(value)));
	}
}
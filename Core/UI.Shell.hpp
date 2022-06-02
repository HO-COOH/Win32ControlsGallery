#pragma once
#include <shellapi.h>
#include <cassert>
namespace UI::Shell
{
	enum class NotifyIconMethod
	{
		Add = NIM_ADD,
		Mofidy = NIM_MODIFY,
		Delete = NIM_DELETE,
		SetFocus = NIM_SETFOCUS,
		SetVersion = NIM_SETVERSION
	};
	inline void NotifyIcon(NotifyIconMethod method, NOTIFYICONDATA& data)
	{
		data.cbSize = sizeof(data);
		assert(Shell_NotifyIcon(static_cast<DWORD>(method), &data));
	}
}
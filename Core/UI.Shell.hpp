#pragma once
#include <shellapi.h>
#include <cassert>
#include <ShObjIdl_core.h>
#include <atlcomcli.h>
#include "Util.Error.hpp"
namespace UI::Shell
{
	enum class NotifyIconMethod
	{
		Add = NIM_ADD,
		Modify = NIM_MODIFY,
		Delete = NIM_DELETE,
		SetFocus = NIM_SETFOCUS,
		SetVersion = NIM_SETVERSION
	};
	inline void NotifyIcon(NotifyIconMethod method, NOTIFYICONDATA& data)
	{
		data.cbSize = sizeof(data);
		assert(Shell_NotifyIcon(static_cast<DWORD>(method), &data));
	}

	class Taskbar
	{
		static auto& GetInstance()
		{
			static CComPtr<ITaskbarList3> instance = []
			{
				CComPtr<ITaskbarList3> instance;
				instance.CoCreateInstance(CLSID_TaskbarList);
				return instance;
			}();
			return instance;
		}
	public:
		enum class ProgressState
		{
			NoProgress = TBPF_NOPROGRESS,
			Indeterminate = TBPF_INDETERMINATE,
			Normal = TBPF_NORMAL,
			Error = TBPF_ERROR,
			Paused = TBPF_PAUSED
		};
		
		static void SetProgressState(HWND hwnd, ProgressState state)
		{
			Util::Error::ThrowOnError(GetInstance()->SetProgressState(hwnd, static_cast<TBPFLAG>(state)));
		}

		static void SetProgressValue(HWND hwnd, ULONGLONG current, ULONGLONG maximum)
		{
			Util::Error::ThrowOnError(GetInstance()->SetProgressValue(hwnd, current, maximum));
		}
	};
}
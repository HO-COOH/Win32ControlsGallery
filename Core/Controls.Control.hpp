#pragma once
#include <Windows.h>
#include <CommCtrl.h>
#include <Shlwapi.h>

extern HMODULE gHinst;
namespace Controls
{
	class Control
	{
	protected:
		HWND m_hwnd;
		inline LRESULT sendMessage(UINT message, WPARAM wParam, LPARAM lParam);
	public:
		using Handle = HWND;
		inline Handle getHandle() const;
		inline void setVisible(bool visible = true);
	};

	LRESULT Control::sendMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		return SendMessage(m_hwnd, message, wParam, lParam);
	}
	Control::Handle Control::getHandle() const
	{
		return m_hwnd;
	}
	void Controls::Control::setVisible(bool visible)
	{
		ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
	}

	inline DWORD StringLength(LPCSTR str)
	{
		return static_cast<DWORD>(strlen(str));
	}

	inline DWORD StringLength(LPCWSTR str)
	{
		return static_cast<DWORD>(wcslen(str));
	}

	inline RECT GetClientRect(HWND hwnd)
	{
		RECT rc{};
		GetClientRect(hwnd, &rc);
		return rc;
	}

	inline DLLVERSIONINFO GetVersion()
	{
		auto const hInstance = LoadLibrary(L"C:\\Windows\\System32\\ComCtl32.dll");
		if (!hInstance)
			return {};

		auto const getVersionProc = reinterpret_cast<DLLGETVERSIONPROC>(
			GetProcAddress(hInstance, "DllGetVersion"));
		if (!getVersionProc)
		{
			FreeLibrary(hInstance);
			return {};
		}

		DLLVERSIONINFO info{};
		info.cbSize = sizeof(info);
		auto hr = getVersionProc(&info);
		FreeLibrary(hInstance);
		return info;
	}

	inline void Init()
	{
		INITCOMMONCONTROLSEX const icce
		{
			.dwSize = sizeof(icce),
			.dwICC = ICC_WIN95_CLASSES
		};
		InitCommonControlsEx(&icce);
	}
}
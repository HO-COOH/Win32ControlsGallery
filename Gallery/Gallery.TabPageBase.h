#pragma once
#include "Gallery.PageBase.h"
#include <windef.h>
#include <WinUser.h>

namespace Gallery
{
	class TabPageBase : public PageBase
	{
	protected:
		HWND m_container;
	public:
		TabPageBase(HWND container, std::wstring name) : PageBase{ std::move(name) },  m_container { container } {}
		
		void show() override { if (m_container) ShowWindow(m_container, SW_SHOW); }
		void hide() override { if (m_container) ShowWindow(m_container, SW_HIDE); }
	};
}
#include "pch.h"
#include "Gallery.Pages.ButtonPage.Page.h"
#include "Gallery.Button.h"
#include <Flags.hpp>

namespace Gallery::Pages::ButtonPage
{
	Page::Page(HWND container) : TabPageBase{container, L"Button"}
	{
		int y = 0;
		int x = 0;
		m_examples.emplace_back(container, x, y, L"Basic Button");
		m_examples.back().addControl<Controls::Button>(
			POINT{0, 0},
			container, 
			Flags<DWORD>{Controls::Button::Style::PushButton}
			
		);
	}
	


}
#include "pch.h"
#include "Gallery.Pages.ProgressBarPage.Page.h"

namespace Gallery::Pages::ProgressBarPage
{
	constexpr static int height = 100;
	constexpr static int width = 300;

	Page::Page(HWND container, int x, int y) :
		TabPageBase{ container, L"Progress bar" },
		m_min{ container, Flags<DWORD>{Controls::TextEdit::Styles::Number, Controls::TextEdit::Styles::Center, WS_BORDER }, x, y++ * height, 200, height },
		m_max{ container, Flags<DWORD>{Controls::TextEdit::Styles::Number, Controls::TextEdit::Styles::Center, WS_BORDER },x, y++ * height, 200, height },
		m_stepAmount{ container, Flags<DWORD>{Controls::TextEdit::Styles::Number, Controls::TextEdit::Styles::Center, WS_BORDER }, x++, y++* height, 200, height },

		m_marqueeMode{ container, L"Marquee Mode", x * width, (y = 0) * height, 200, height },
		m_smooth{ container, L"Smooth", x * width, ++y * height, 200, height },
		m_smoothReverse{ container, L"Smooth reverse", x * width, ++y * height, 200, height },
		m_vertical{ container, L"Vertical", x * width, ++y * height, 200, height },
		
		m_stepButton{container, Flags<DWORD>(Controls::Button::Style::PushButton), x * width, ++y * height, 200, height},
		m_stepValue{container, 0, 600, 200, 100 },
		m_bar{container, 0, 0, 700, 1000, 100}
	{
		m_bar.setPos(50);
		m_stepButton.setText(L" → ");
		m_stepValue.setText(L"Header:");
	}
}
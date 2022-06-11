#pragma once
#include "pch.h"
#include "Gallery.Pages.ProgressBarPage.ProgrssBarCheckbox.h"

namespace Gallery::Pages::ProgressBarPage
{
	ProgressBarCheckbox::ProgressBarCheckbox(HWND container, LPCTSTR text, int x, int y, int width, int height, Controls::ProgressBar* bar, DWORD style) :
		Gallery::Checkbox{ container, text, x, y, width, height },
		m_progressBar{bar}
	{
		if (m_progressBar)
		{
			onClick([this, style](HWND) mutable
			{
				auto oldStyle = GetWindowLongPtr(m_hwnd, GWL_STYLE);
				style |= oldStyle;
				SetWindowLongPtr(m_hwnd, GWL_STYLE, style);
			});
		}
	}
}
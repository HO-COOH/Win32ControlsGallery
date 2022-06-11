#pragma once

#include "Gallery.Button.h"
#include <Controls.ProgressBar.hpp>

namespace Gallery::Pages::ProgressBarPage
{
	class ProgressBarCheckbox : public Gallery::Checkbox
	{
		Controls::ProgressBar* m_progressBar{};
	public:
		ProgressBarCheckbox(HWND container, LPCTSTR text, int x, int y, int width, int height, Controls::ProgressBar* bar, DWORD style);
	};
}
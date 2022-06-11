#pragma once
#include "Gallery.TabPageBase.h"
#include <Controls.ProgressBar.hpp>
#include <Controls.TextEdit.hpp>
#include "Gallery.Button.h"
#include "Gallery.Spinbox.h"
namespace Gallery::Pages::ProgressBarPage
{
	class Page : public TabPageBase
	{
		Controls::TextEdit m_min;
		Controls::TextEdit m_max;
		Controls::TextEdit m_stepAmount;
		
		//styles
		Checkbox m_marqueeMode;
		Checkbox m_smooth;
		Checkbox m_smoothReverse;
		Checkbox m_vertical;
		
		ButtonEx m_stepButton;
		
		SpinboxWithHeader m_stepValue;

		Controls::ProgressBar m_bar;
	public:
		Page(HWND container, int x = 0, int y = 0);
	};
}
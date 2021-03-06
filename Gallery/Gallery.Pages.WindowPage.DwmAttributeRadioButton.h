#pragma once
#include "Gallery.Button.h"
namespace Gallery::Pages::WindowPage
{
	template<typename ValueType>
	class DwmAttributeRadioButton : public RadioButton
	{
		DWORD const m_attribute{};
		ValueType const m_enableValue;
		ValueType const m_disableValue;
	public:
		
		DwmAttributeRadioButton(HWND parent, LPCTSTR text, int x, int y, int width, int height, DWORD attribute, ValueType enableValue, ValueType disableValue = {})
			: RadioButton(parent, text, x, y, width, height), m_attribute{ attribute }, m_enableValue{ enableValue }, m_disableValue{ disableValue }
		{

		}

		void addHandler()
		{
			onClick([this](HWND)
			{
				if (gCreatedWindow)
				{
					DwmSetWindowAttribute(gCreatedWindow, m_attribute,
						isChecked() ? &m_enableValue : &m_disableValue, sizeof(ValueType));
				}
			});
		}
	};
}
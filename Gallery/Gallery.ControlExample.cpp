#include "pch.h"
#include "Gallery.ControlExample.h"
#include <Flags.hpp>

namespace Gallery
{
	ControlExample::ControlExample(
		HWND parent,
		int x, 
		int y, 
		LPCWSTR title, 
		int preservedWidth, 
		int preservedHeight) :
		m_header
		{
			parent,
			Flags<DWORD>{Controls::TextEdit::Styles::ReadOnly},
			x, y, 300, TitleHeight
		}
	{
		m_content.onAddControl(RECT{ x, y, x + 300, y + TitleHeight });
		m_header.setText(title);
	}
	
	Content const& ControlExample::getContent() const
	{
		return m_content;
	}
}
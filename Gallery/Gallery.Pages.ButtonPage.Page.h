#pragma once
#include "Gallery.TabPageBase.h"
#include "Gallery.ControlExample.h"
namespace Gallery::Pages::ButtonPage
{
	class Page : public TabPageBase
	{
		std::vector<ControlExample> m_examples;
	public:
		Page(HWND container);

	};

}
#pragma once
#include "Gallery.TabPageBase.h"

namespace Gallery::Pages::ButtonPage
{
	class Page : public TabPageBase
	{
		static Content GetSimpleButtonContent();
		
	public:
		Page(HWND container);

		// Inherited via PageBase
		virtual void hide() override;
		virtual void show() override;
	};

}
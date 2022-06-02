#include "pch.h"
#include "Gallery.Pages.ButtonPage.Page.h"
#include "Gallery.Button.h"

namespace Gallery::Pages::ButtonPage
{
	Content Page::GetSimpleButtonContent()
	{
		//auto button = std::make_unique<ButtonEx>();
		//button->setText("Standard Win32 Button");
		//Content content;
		//content.add(std::move(button));
		//return content;
		return{};
	}

	Page::Page(HWND container) : TabPageBase{container, L"Button"}
	{
	}

	void Page::hide()
	{
	}

	void Page::show()
	{
	}

}
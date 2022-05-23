#include "pch.h"
#include "Gallery.Pages.ButtonPage.Page.h"
#include "Gallery.Button.h"

namespace Gallery
{
	Content ButtonPage::GetSimpleButtonContent()
	{
		//auto button = std::make_unique<ButtonEx>();
		//button->setText("Standard Win32 Button");
		//Content content;
		//content.add(std::move(button));
		//return content;
		return{};
	}

	ButtonPage::ButtonPage() : PageBase{L"Button"}
	{
	}

	void ButtonPage::hide()
	{
	}

	void ButtonPage::show()
	{
	}

}
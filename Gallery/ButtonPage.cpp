#include "pch.h"
#include "ButtonPage.h"
#include "Gallery.Button.h"


Content ButtonPage::GetSimpleButtonContent()
{
	//auto button = std::make_unique<ButtonEx>();
	//button->setText("Standard Win32 Button");
	//Content content;
	//content.add(std::move(button));
	//return content;
	return{};
}

ButtonPage::ButtonPage()
{
	//A simple button
	ControlExample simpleButtonExample;
	simpleButtonExample.setHeaderText("A simple button with text");
	simpleButtonExample.setContent(GetSimpleButtonContent());
	addExample(std::move(simpleButtonExample));
}

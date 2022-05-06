#pragma once
#include "ControlBase.h"
#include <string>

class ButtonEx : public ControlBase
{
public:
	void setText(std::string&& text);
};


#pragma once
#include "ControlExample.h"

namespace Gallery
{
	class PageBase
	{
		std::wstring m_name;
	public:
		PageBase(std::wstring name);
		void addExample(ControlExample&& example);
		std::wstring_view getName() const;


		virtual void hide() = 0;
		virtual void show() = 0;
	};

}
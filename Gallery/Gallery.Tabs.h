#pragma once
#include <vector>
#include "Gallery.PageBase.h"
#include <memory>
#include "Handler.hpp"
namespace Gallery
{
	class Tabs : private Controls::Tab
	{
		std::vector<std::unique_ptr<PageBase>> m_pages;
		
		
	public:

		static inline Handler<HWND, void(NMHDR const*)> OnSelectionChangeHandlers;

		Tabs(HWND parent, std::vector<std::unique_ptr<PageBase>> pages);
		Tabs(HWND parent);
		Tabs& operator+=(std::unique_ptr<PageBase>&& page);
	};

}

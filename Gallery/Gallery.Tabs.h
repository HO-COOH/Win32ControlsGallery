#pragma once
#include <vector>
#include "Gallery.PageBase.h"
#include <memory>
#include "Handler.hpp"
namespace Gallery
{
	class Tabs : public Controls::Tab
	{
		std::vector<std::unique_ptr<PageBase>> m_pages;
		
		int m_currentShowingPage = -1;
		void addHandler();
		void setCurrentShowingPage(int selection);

		static void RegisterContainer();
	public:

		static inline Handler<HWND, void(NMHDR const*)> OnSelectionChangeHandlers;

		Tabs(HWND parent, std::vector<std::unique_ptr<PageBase>> pages);
		Tabs(HWND parent);
		Tabs& operator+=(std::unique_ptr<PageBase>&& page);

		std::unique_ptr<PageBase>& getCurrentShowingPage();
		[[nodiscard]] HWND getContainerWindow();
	};

}

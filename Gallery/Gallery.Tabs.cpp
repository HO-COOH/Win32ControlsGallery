#include "pch.h"
#include "Gallery.Tabs.h"

namespace Gallery
{
    Tabs::Tabs(HWND parent, std::vector<std::unique_ptr<PageBase>> pages) :
        Controls::Tab(parent),
        m_pages(std::move(pages))
    {
    }
    Tabs::Tabs(HWND parent) : Controls::Tab(parent)
    {
        OnSelectionChangeHandlers.add(getHandle(), [this](NMHDR const* info)
        {
               OutputDebugString(L"changed");
        });
    }
    Tabs& Tabs::operator+=(std::unique_ptr<PageBase>&& page)
    {
        m_pages.emplace_back(std::move(page));
        return *this;
    }
}
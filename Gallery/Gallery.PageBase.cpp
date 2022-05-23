#include "pch.h"
#include "Gallery.PageBase.h"

namespace Gallery
{
	PageBase::PageBase(std::wstring name) : m_name(std::move(name))
	{
	}
	void PageBase::addExample(ControlExample&& example)
	{
	}
	std::wstring_view PageBase::getName() const
	{
		return m_name;
	}
}
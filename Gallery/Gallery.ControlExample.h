#pragma once
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#define NOMINMAX
#include <Controls.Control.hpp>
#include <Controls.TextEdit.hpp>

namespace Gallery
{

	class Content
	{
		struct Dimension
		{
			int xMin;
			int xMax;
			int yMin;
			int yMax;

		};

		std::vector<std::unique_ptr<Controls::Control>> m_controls;
	public:
		Dimension m_dimension{};

		void onAddControl(RECT rect)
		{
			m_dimension.xMin = std::min<int>(m_dimension.xMin, rect.left);
			m_dimension.xMax = std::max<int>(m_dimension.xMax, rect.right);
			m_dimension.yMin = std::min<int>(m_dimension.yMin, rect.top);
			m_dimension.yMax = std::max<int>(m_dimension.yMax, rect.bottom);
		}

		void addControl(RECT rect, std::unique_ptr<Controls::Control>&& control)
		{
			m_controls.emplace_back(std::move(control));
			onAddControl(rect);
		}
	};

	class ControlExample
	{
		Controls::TextEdit m_header;
		
		Content m_content;
	public:
		//Constants
		constexpr static inline auto VerticalSpacing = 50;
		constexpr static inline auto TitleHeight = 50;
		
		//Set up titles and initial position
		ControlExample(
			HWND parent,
			int x, 
			int y, 
			LPCWSTR title, 
			int preservedWidth = -1, 
			int preservedHeight = -1);
		
		Content const& getContent() const;
		
		template<typename Control, typename...Args>
		ControlExample& addControl(POINT pos, Args&&... args);
	};


	template<typename Control, typename...Args>
	ControlExample& ControlExample::addControl(POINT pos, Args&&... args)
	{
		auto newControl = std::make_unique<Control>(std::forward<Args>(args)...);
		pos.y += TitleHeight;
		newControl->move(pos.x, pos.y);
		RECT rect{};
		GetClientRect(newControl->getHandle(), &rect);
		m_content.addControl(rect, std::move(newControl));
		return *this;
	}
}
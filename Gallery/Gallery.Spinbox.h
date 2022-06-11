#pragma once
#include <Controls.TextEdit.hpp>
#include <Controls.UpDown.hpp>
#include <Controls.Static.hpp>
#include <Flags.hpp>
#include "Handler.hpp"
namespace Gallery
{
	class Spinbox
	{
		Controls::TextEdit m_numberBox;
		Controls::UpDown m_upDown;
		
	public:
		static inline Handler<HWND, bool(NMUPDOWN*)> OnValueChangeHandlers;
		Spinbox(HWND parent, int x, int y, int width, int height) :
			m_numberBox{parent, static_cast<DWORD>(Controls::TextEdit::Styles::Left) | static_cast<DWORD>(Controls::TextEdit::Styles::Number),
		x, y, width, height},
			m_upDown{parent, static_cast<DWORD>(Controls::UpDown::Styles::AlignRight) | static_cast<DWORD>(Controls::UpDown::Styles::AutoBuddy) | static_cast<DWORD>(Controls::UpDown::Styles::SetBuddyInt), 0, 0, 0, 0, m_numberBox.getHandle()}
		{
			m_upDown.setRange(0, 100);
		}

		template<typename Handler>
		void onValueChange(Handler&& handler)
		{
			OnValueChangeHandlers.add(m_upDown.getHandle(), std::forward<Handler>(handler));
		}
	};

	class SpinboxWithHeader : public Spinbox
	{
		Controls::Static m_header;
	public:
		SpinboxWithHeader(HWND parent, int x, int y, int width, int height, LPCTSTR header = nullptr) :
			Spinbox{ parent, x, y + 50, width, height - 50 },
			m_header{ parent, Flags<DWORD>{Controls::Static::Styles::Left}, x, y, width, 50 }
		{
			if (header)
				m_header.setText(header);
		}

		void setText(LPCTSTR header)
		{
			m_header.setText(header);
		}
	};
}
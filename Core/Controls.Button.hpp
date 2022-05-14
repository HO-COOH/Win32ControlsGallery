#pragma once

#include "Controls.Control.hpp"
#include <WinUser.h>
#include <windowsx.h>
namespace Controls
{
	class Button : public Control
	{
	public:
		enum class Style
		{
			ThreeState = BS_3STATE,
			AutoThreeState = BS_AUTO3STATE,
			AutoCheckbox = BS_AUTOCHECKBOX,
			AutoRadioButton = BS_AUTORADIOBUTTON,
			Bitmap = BS_BITMAP,
			Bottom = BS_BOTTOM,
			Center = BS_CENTER,
			Checkbox = BS_CHECKBOX,
			CommandLink = BS_COMMANDLINK,
			DefCommandLink = BS_DEFCOMMANDLINK,
			DefPushButton = BS_DEFPUSHBUTTON,
			DefSplitButton = BS_DEFSPLITBUTTON,
			Groupbox = BS_GROUPBOX,
			Icon = BS_ICON,
			Flat = BS_FLAT,
			Left = BS_LEFT,
			LeftText = BS_LEFTTEXT,
			MultiLine = BS_MULTILINE,
			Notify = BS_NOTIFY,
			OwnerDraw = BS_OWNERDRAW,
			PushButton = BS_PUSHBUTTON,
			RadioButton = BS_RADIOBUTTON,
			Right = BS_RIGHT,
			RightButton = BS_RIGHTBUTTON,
			SplitButton = BS_SPLITBUTTON,
			Text = BS_TEXT,
			Top = BS_TOP,
			TypeMask = BS_TYPEMASK,
			UserButton = BS_USERBUTTON,
			VCenter = BS_VCENTER
		};

		enum Message
		{
			HotItemChange = BCN_HOTITEMCHANGE,
			Clicked = BN_CLICKED,
			DoubleClicked = BN_DBLCLK,
			Disable = BN_DISABLE,
			Pushed = BN_PUSHED,
			Unpushed = BN_UNPUSHED,
			KillFocus = BN_KILLFOCUS,
			Paint = BN_PAINT,
			SetFocus = BN_SETFOCUS,
		};


		inline Button(HWND parent);
		inline Button(HWND parent, DWORD style);
		inline Button(HWND parent, DWORD style, int x, int y, int width, int height);

		//methods
		inline void setText(LPCTSTR text);
		inline void getIdealSize(SIZE& size);
		inline void setCheck(int check);



		//Constants
		constexpr static auto ClassName = WC_BUTTON;
	};

	Button::Button(HWND parent)
	{
		auto const rcClient = GetClientRect(parent);
		m_hwnd = CreateWindow(
			ClassName,
			L"",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			0, 0, rcClient.right / 2, rcClient.bottom / 2,
			parent,
			NULL,
			gHinst,
			NULL);
	}
	Button::Button(HWND parent, DWORD style)
	{
		auto const rcClient = GetClientRect(parent);
		m_hwnd = CreateWindow(
			ClassName,
			L"",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | style,
			0, 0, rcClient.right / 2, rcClient.bottom / 2,
			parent,
			NULL,
			gHinst,
			NULL);
	}
	Button::Button(HWND parent, DWORD style, int x, int y, int width, int height)
	{
		m_hwnd = CreateWindow(
			ClassName,
			L"",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | style,
			x, y, width, height,
			parent,
			NULL,
			gHinst,
			NULL);
	}
	void Button::setText(LPCTSTR text)
	{
		Button_SetText(m_hwnd, text);
	}
	void Button::getIdealSize(SIZE& size)
	{
		sendMessage(BCM_GETIDEALSIZE, 0, reinterpret_cast<LPARAM>(&size));
	}
	void Button::setCheck(int check)
	{
		Button_SetCheck(m_hwnd, check);
	}
}
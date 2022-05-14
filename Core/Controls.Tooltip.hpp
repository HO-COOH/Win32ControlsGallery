#pragma once
#include "Controls.Control.hpp"
#include <WinUser.h>

namespace Controls
{	

	class Tooltip : public Control
	{
	public:
		enum Message
		{
			CustomDraw = NM_CUSTOMDRAW,
			GeiDispInfo = TTN_GETDISPINFO,
			LinkClick = TTN_LINKCLICK,
			NeedText = TTN_NEEDTEXT,
			Pop = TTN_POP,
			Show = TTN_SHOW
		};

		enum Style
		{
			AlwaysTip = TTS_ALWAYSTIP,
			Ballon = TTS_BALLOON,
			NoAnimate = TTS_NOANIMATE,
			NoFade = TTS_NOFADE,
			NoPrefix = TTS_NOPREFIX,
			UseVisualStyle = TTS_USEVISUALSTYLE
		};

		enum class Icon
		{
			None = TTI_NONE,
			Info = TTI_INFO,
			Warning = TTI_WARNING,
			Error = TTI_ERROR,
			InfoLarge = TTI_INFO_LARGE,
			WarningLarge = TTI_WARNING_LARGE,
			ErrorLarge = TTI_ERROR_LARGE
		};

		enum class Delay
		{
			AutoPop = TTDT_AUTOPOP,
			Initial = TTDT_INITIAL,
			Reshow = TTDT_RESHOW,
			Automatic = TTDT_AUTOMATIC
		};


		inline Tooltip(HWND parent, DWORD style);

		//methods
		inline void activate();
		inline void deactivate();
		inline void addTool(TOOLINFO const& toolInfo);
		inline void adjustRect(BOOL textToWindow, RECT& rect);
		inline void delTool(TOOLINFO const& toolInfo);
		inline BOOL enumTool(int i, TOOLINFO& info);
		inline SIZE getBubbleSize(TOOLINFO const& info);
		inline BOOL getCurrentTool(TOOLINFO& info);
		inline BOOL getCurrentTool();
		inline INT getDelayTime(Delay delayType); //milliseconds
		inline void getMargin(RECT& margin);
		inline INT getMaxTipWidth();
		inline void getText(WPARAM count, TOOLINFO& info);
		inline COLORREF getTipBkColor();
		inline COLORREF getTipTextColor();
		inline void getTitle(TTGETTITLE& title);
		inline INT getToolCount();
		inline BOOL getToolInfo(TOOLINFO& toolInfo);
		inline BOOL hitTest(TTHITTESTINFO const& info);
		inline void newToolRect(TOOLINFO const& info);
		inline void pop();
		inline void popUp();
		inline void relayEvent(MSG const& msg);
		inline void setDelayTime(Delay delay, int milliseconds);
		inline void setMargin(RECT const& margin);
		inline int setMaxTipWidth(int maxWidth);
		inline void setTipBkColor(COLORREF backgroundColor);
		inline void setTipTextColor(COLORREF textColor);
		inline BOOL setTitle(Icon icon, LPCTSTR title);
		inline void setToolInfo(TOOLINFO const& info);
		inline void setWindowTheme(LPCTSTR visualStyle);
		inline void trackActivate(BOOL activate, TOOLINFO const& info);
		inline void trackPosition(int x, int y);
		inline void update();
		inline void updateTipText(TOOLINFO const& info);
		inline HWND windowFromPoint(POINT p);

		//Constants
		constexpr static auto ClassName = TOOLTIPS_CLASS;
	};


    Tooltip::Tooltip(HWND parent, DWORD style)
    {
        m_hwnd = CreateWindowEx(
            WS_EX_TOPMOST, ClassName, NULL, WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON | style,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            parent, NULL, gHinst, NULL);
    }
    void Tooltip::activate()
    {
        SendMessage(m_hwnd, TTM_ACTIVATE, TRUE, 0);
    }
    void Tooltip::deactivate()
    {
        SendMessage(m_hwnd, TTM_ACTIVATE, FALSE, 0);
    }
    void Tooltip::addTool(TOOLINFO const& toolInfo)
    {
        SendMessage(m_hwnd, TTM_ADDTOOL, 0, reinterpret_cast<LPARAM>(&toolInfo));
    }

    void Tooltip::adjustRect(BOOL textToWindow, RECT& rect)
    {
        SendMessage(m_hwnd, TTM_ADJUSTRECT, textToWindow, reinterpret_cast<LPARAM>(&rect));
    }

    void Tooltip::delTool(TOOLINFO const& toolInfo)
    {
        sendMessage(TTM_DELTOOL, 0, reinterpret_cast<LPARAM>(&toolInfo));
    }
    BOOL Tooltip::enumTool(int i, TOOLINFO& info)
    {
        return sendMessage(TTM_ENUMTOOLS, i, reinterpret_cast<LPARAM>(&info));
    }
    SIZE Tooltip::getBubbleSize(TOOLINFO const& info)
    {
        auto const result = sendMessage(TTM_GETBUBBLESIZE, 0, reinterpret_cast<LPARAM>(&info));
        return SIZE{ .cx = LOWORD(result), .cy = HIWORD(result) };
    }
    BOOL Tooltip::getCurrentTool(TOOLINFO& info)
    {
        return sendMessage(TTM_GETCURRENTTOOL, 0, reinterpret_cast<LPARAM>(&info));
    }
    BOOL Tooltip::getCurrentTool()
    {
        return sendMessage(TTM_GETCURRENTTOOL, 0, NULL);
    }
    INT Tooltip::getDelayTime(Delay delayType)
    {
        return sendMessage(TTM_GETDELAYTIME, static_cast<WPARAM>(delayType), 0);
    }
    void Tooltip::getMargin(RECT& margin)
    {
        sendMessage(TTM_GETMARGIN, 0, reinterpret_cast<LPARAM>(&margin));
    }
    INT Tooltip::getMaxTipWidth()
    {
        return sendMessage(TTM_GETMAXTIPWIDTH, 0, 0);
    }

    void Tooltip::getText(WPARAM count, TOOLINFO& info)
    {
        sendMessage(TTM_GETTEXT, count, reinterpret_cast<LPARAM>(&info));
    }

    COLORREF Tooltip::getTipBkColor()
    {
        return sendMessage(TTM_GETTIPBKCOLOR, 0, 0);
    }

    COLORREF Tooltip::getTipTextColor()
    {
        return sendMessage(TTM_GETTIPTEXTCOLOR, 0, 0);
    }

    void Tooltip::getTitle(TTGETTITLE& title)
    {
        sendMessage(TTM_GETTITLE, 0, reinterpret_cast<LPARAM>(&title));
    }

    INT Tooltip::getToolCount()
    {
        return sendMessage(TTM_GETTOOLCOUNT, 0, 0);
    }

    BOOL Tooltip::getToolInfo(TOOLINFO& toolInfo)
    {
        return sendMessage(TTM_GETTOOLINFO, 0, reinterpret_cast<LPARAM>(&toolInfo));
    }

    BOOL Tooltip::hitTest(TTHITTESTINFO const& info)
    {
        return sendMessage(TTM_HITTEST, 0, reinterpret_cast<LPARAM>(&info));
    }

    void Tooltip::newToolRect(TOOLINFO const& info)
    {
        sendMessage(TTM_NEWTOOLRECT, 0, reinterpret_cast<LPARAM>(&info));
    }

    void Tooltip::pop()
    {
        sendMessage(TTM_POP, 0, 0);
    }

    void Tooltip::popUp()
    {
        sendMessage(TTM_POPUP, 0, 0);
    }

    void Tooltip::relayEvent(MSG const& msg)
    {
        sendMessage(TTM_RELAYEVENT, 0, reinterpret_cast<LPARAM>(&msg));
    }

    void Tooltip::setDelayTime(Delay delay, int milliseconds)
    {
        sendMessage(TTM_SETDELAYTIME, static_cast<WPARAM>(delay),
            static_cast<LPARAM>(milliseconds));
    }

    void Tooltip::setMargin(RECT const& margin)
    {
        sendMessage(TTM_SETMARGIN, 0, reinterpret_cast<LPARAM>(&margin));
    }

    int Tooltip::setMaxTipWidth(int maxWidth)
    {
        return sendMessage(TTM_SETMAXTIPWIDTH, 0, maxWidth);
    }

    void Tooltip::setTipBkColor(COLORREF backgroundColor)
    {
        sendMessage(TTM_SETTIPBKCOLOR, backgroundColor, 0);
    }

    void Tooltip::setTipTextColor(COLORREF textColor)
    {
        sendMessage(TTM_SETTIPTEXTCOLOR, textColor, 0);
    }

    BOOL Tooltip::setTitle(Icon icon, LPCTSTR title)
    {
        return sendMessage(TTM_SETTITLE,
            static_cast<WPARAM>(icon),
            reinterpret_cast<LPARAM>(title));
    }

    void Tooltip::setToolInfo(TOOLINFO const& info)
    {
        sendMessage(TTM_SETTOOLINFO, 0, reinterpret_cast<LPARAM>(&info));
    }

    void Tooltip::setWindowTheme(LPCTSTR visualStyle)
    {
        sendMessage(TTM_SETWINDOWTHEME, 0, reinterpret_cast<LPARAM>(visualStyle));
    }

    void Tooltip::trackActivate(BOOL activate, TOOLINFO const& info)
    {
        sendMessage(TTM_TRACKACTIVATE, activate, reinterpret_cast<LPARAM>(&info));
    }

    void Tooltip::trackPosition(int x, int y)
    {
        sendMessage(TTM_TRACKPOSITION, 0, MAKEWPARAM(x, y));
    }

    void Tooltip::update()
    {
        sendMessage(TTM_UPDATE, 0, 0);
    }

    void Tooltip::updateTipText(TOOLINFO const& info)
    {
        sendMessage(TTM_UPDATETIPTEXT, 0, reinterpret_cast<LPARAM>(&info));
    }

    HWND Tooltip::windowFromPoint(POINT p)
    {
        return reinterpret_cast<HWND>(sendMessage(
            TTM_WINDOWFROMPOINT, 0, reinterpret_cast<LPARAM>(&p)));
    }
}
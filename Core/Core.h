#pragma once

#include "resource.h"
#include <Shlwapi.h>

namespace Controls
{
	void InitWindow();
	void InitControls();
	void Init();
	
	DWORD StringLength(LPCSTR str);
	DWORD StringLength(LPCWSTR str);
	
	RECT GetClientRect(HWND hwnd);

	class Control
	{
	protected:
		HWND m_hwnd;
		LRESULT sendMessage(UINT message, WPARAM wParam, LPARAM lParam);
	public:
		using Handle = HWND;
		Handle getHandle() const;
		void setVisible(bool visible = true);
	};

	class Tab : public Control
	{

	public:
		Tab(HWND parent);

		void addTab(TCITEM const& item);
		void addTab(LPCTSTR text);

		//methods
		void adjustRect(BOOL larger, RECT& rect);
		void deleteAllItems();
		void deleteItem(int i);
		void deselectAll(UINT excludeFocus);
		int getCurFocus();
		int getCurSel() const; //wrong doc
		DWORD getExtendedStyle();
		HIMAGELIST getImageList();
		TCITEM getItem(int iItem, UINT mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT);
		int getItemCount();
		RECT getItemRect(int i);
		int getRowCount();
		HWND getToolTips();
		BOOL getUnicodeFormat();
		void highlightItem(int i, WORD highlight);
		int hitTest(TCHITTESTINFO const& info);
		void removeImage(int i);
		void setCurFocus(int i);
		void setExtendedStyle(DWORD styles);
		void setImageList(HIMAGELIST list);
		void setItem(int i, TCITEM const& item);
		void setItemExtra(int extraBytes);
		void setItemSize(int x, int y);
		void setMinTabWidth(int x);
		void setPadding(int cx, int cy);
		void setToolTips(HWND tooltip);
		void setUnicodeFormat(BOOL unicode);
		
		//Constants
		constexpr static auto ClassName = WC_TABCONTROL;
	};

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


		Button(HWND parent);
		Button(HWND parent, DWORD style);

		Button(HWND parent, DWORD style, int x, int y, int width, int height);

		//methods
		void setText(LPCTSTR text);
		void getIdealSize(SIZE& size);
		void setCheck(int check);
		
		
		
		//Constants
		constexpr static auto ClassName = WC_BUTTON;
	};

	class Tooltip : public Control
	{
	public:
		enum Message
		{
			CustomDraw = NM_CUSTOMDRAW,
			GeiDispInfo	= TTN_GETDISPINFO,
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

		
		Tooltip(HWND parent, DWORD style);

		//methods
		void activate();
		void deactivate();
		void addTool(TOOLINFO const& toolInfo);
		void adjustRect(BOOL textToWindow, RECT& rect);
		void delTool(TOOLINFO const& toolInfo);
		BOOL enumTool(int i, TOOLINFO& info);
		SIZE getBubbleSize(TOOLINFO const& info);
		BOOL getCurrentTool(TOOLINFO& info);
		BOOL getCurrentTool();
		INT getDelayTime(Delay delayType); //milliseconds
		void getMargin(RECT& margin);
		INT getMaxTipWidth();
		void getText(WPARAM count, TOOLINFO& info);
		COLORREF getTipBkColor();
		COLORREF getTipTextColor();
		void getTitle(TTGETTITLE& title);
		INT getToolCount();
		BOOL getToolInfo(TOOLINFO& toolInfo);
		BOOL hitTest(TTHITTESTINFO const& info);
		void newToolRect(TOOLINFO const& info);
		void pop();
		void popUp();
		void relayEvent(MSG const& msg);
		void setDelayTime(Delay delay, int milliseconds);
		void setMargin(RECT const& margin);
		int setMaxTipWidth(int maxWidth);
		void setTipBkColor(COLORREF backgroundColor);
		void setTipTextColor(COLORREF textColor);
		BOOL setTitle(Icon icon, LPCTSTR title);
		void setToolInfo(TOOLINFO const& info);
		void setWindowTheme(LPCTSTR visualStyle);
		void trackActivate(BOOL activate, TOOLINFO const& info);
		void trackPosition(int x, int y);
		void update();
		void updateTipText(TOOLINFO const& info);
		HWND windowFromPoint(POINT p);

		//Constants
		constexpr static auto ClassName = TOOLTIPS_CLASS;
	};

	class Trackbar : public Control
	{
		
	public:
		enum Style
		{
			AutoTicks = TBS_AUTOTICKS,
			Vert = TBS_VERT,
			Horz = TBS_HORZ,
			Top = TBS_TOP,
			Bottom = TBS_BOTTOM,
			Left = TBS_LEFT,
			Right = TBS_RIGHT,
			Both = TBS_BOTH,
			NoTicks = TBS_NOTICKS,
			EnableSelRange = TBS_ENABLESELRANGE,
			FixedLength = TBS_FIXEDLENGTH,
			NoThumb = TBS_NOTHUMB,
			ToolTips = TBS_TOOLTIPS,
			Reversed = TBS_REVERSED,
			DownIsLeft = TBS_DOWNISLEFT,
			NotifyBeforeMove = TBS_NOTIFYBEFOREMOVE,
			TransparentBkGnd = TBS_TRANSPARENTBKGND
		};

		Trackbar(HWND parent, DWORD style, int x, int y, int width, int height);

		//methods
		void setRange(int min, int max);
		int getPos();
		void setPos(bool redraw, int position);
		
		//Constants
		constexpr static auto ClassName = TRACKBAR_CLASS;
	};

	DLLVERSIONINFO GetVersion();
}
// Core.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Core.h"
#include <windowsx.h>
#include <cassert>
#include <iostream>
#include <sstream>
#include <future>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

static HINSTANCE gHinst;
static HWND gHwnd;
static HWND gCreatedWindow;
static int gNCmdShow;
#define MAX_LOADSTRING 100

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        //case WM_NCCALCSIZE:
        //    return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            auto redBrush = CreateSolidBrush(RGB(255, 0, 0));

            FillRect(hdc, &ps.rcPaint, redBrush);

            EndPaint(hWnd, &ps);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

namespace Controls
{
    //
    //  FUNCTION: MyRegisterClass()
    //
    //  PURPOSE: Registers the window class.
    //
    static ATOM MyRegisterClass(HINSTANCE hInstance)
    {
        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CORE));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CORE);
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassExW(&wcex);
    }


    BOOL InitInstance(int nCmdShow)
    {

        gHwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, gHinst, nullptr);

        if (!gHwnd)
        {
            return FALSE;
        }

        ShowWindow(gHwnd, nCmdShow);
        UpdateWindow(gHwnd);

        return TRUE;
    }
	
	
    void InitWindow()
    {
        // Initialize global strings
        LoadStringW(gHinst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadStringW(gHinst, IDC_CORE, szWindowClass, MAX_LOADSTRING);
        MyRegisterClass(gHinst);

        // Perform application initialization:
        if (!InitInstance(gNCmdShow))
        {
            return;
        }


    }

    void InitControls()
    {
        INITCOMMONCONTROLSEX const icce
        {
            .dwSize = sizeof(icce),
            .dwICC = ICC_WIN95_CLASSES
        };
        InitCommonControlsEx(&icce);
    }
	
    void Init()
    {
        SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        InitWindow();
        InitControls();
    }

    DWORD StringLength(LPCSTR str)
    {
        return static_cast<DWORD>(strlen(str));
    }

    DWORD StringLength(LPCWSTR str)
    {
        return static_cast<DWORD>(wcslen(str));
    }

    RECT GetClientRect(HWND hwnd)
    {
        RECT rc{};
		GetClientRect(hwnd, &rc);
		return rc;
    }

    Tab::Tab(HWND parent)
    {
        auto const rcClient = GetClientRect(parent);
        m_hwnd = CreateWindow(
			ClassName,
			L"",
			WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0, 0, rcClient.right, rcClient.bottom,
			parent,
			nullptr,
			gHinst,
			nullptr);
        
    }

    void Tab::addTab(TCITEM const& item)
    {
		TabCtrl_InsertItem(m_hwnd, 0, &item);
    }

    void Tab::addTab(LPCTSTR text)
    {
        TCITEM item
        {
			.mask = TCIF_TEXT,
            .pszText = const_cast<LPTSTR>(text),
			.cchTextMax = static_cast<int>(StringLength(text))
        };
        addTab(item);
    }

    void Tab::adjustRect(BOOL larger, RECT& rect)
    {
		TabCtrl_AdjustRect(m_hwnd, larger, &rect);
    }

    void Tab::deleteAllItems()
    {
        TabCtrl_DeleteAllItems(m_hwnd);
    }

    void Tab::deleteItem(int i)
    {
        TabCtrl_DeleteItem(m_hwnd, i);
    }

    void Tab::deselectAll(UINT excludeFocus)
    {
        TabCtrl_DeselectAll(m_hwnd, excludeFocus);
    }

    int Tab::getCurFocus()
    {
        return TabCtrl_GetCurFocus(m_hwnd);
    }

    int Tab::getCurSel() const
    {
        return TabCtrl_GetCurSel(m_hwnd);
    }
    DWORD Tab::getExtendedStyle()
    {
        return TabCtrl_GetExtendedStyle(m_hwnd);
    }
    HIMAGELIST Tab::getImageList()
    {
        return TabCtrl_GetImageList(m_hwnd);
    }
    TCITEM Tab::getItem(int iItem, UINT mask)
    {
        TCITEM item
        {
            .mask = mask
        };
		TabCtrl_GetItem(m_hwnd, iItem, &item);
        return item;
    }
    int Tab::getItemCount()
    {
        return TabCtrl_GetItemCount(m_hwnd);
    }
    RECT Tab::getItemRect(int i)
    {
        RECT rc{};
		TabCtrl_GetItemRect(m_hwnd, i, &rc);
		return rc;
    }
    int Tab::getRowCount()
    {
        return TabCtrl_GetRowCount(m_hwnd);
    }
    HWND Tab::getToolTips()
    {
        return TabCtrl_GetToolTips(m_hwnd);
    }
    BOOL Tab::getUnicodeFormat()
    {
        return TabCtrl_GetUnicodeFormat(m_hwnd);
    }
    void Tab::highlightItem(int i, WORD highlight)
    {
        TabCtrl_HighlightItem(m_hwnd, i, highlight);
    }
    int Tab::hitTest(TCHITTESTINFO const& info)
    {
		return TabCtrl_HitTest(m_hwnd, &info);
    }
    void Tab::removeImage(int i)
    {
        TabCtrl_RemoveImage(m_hwnd, i);
    }
    void Tab::setCurFocus(int i)
    {
        TabCtrl_SetCurFocus(m_hwnd, i);
    }
    void Tab::setExtendedStyle(DWORD styles)
    {
        TabCtrl_SetExtendedStyle(m_hwnd, styles);
    }
    void Tab::setImageList(HIMAGELIST list)
    {
        TabCtrl_SetImageList(m_hwnd, list);
    }
    void Tab::setItem(int i, TCITEM const& item)
    {
        TabCtrl_SetItem(m_hwnd, i, &item);
    }
    void Tab::setItemExtra(int extraBytes)
    {
        TabCtrl_SetItemExtra(m_hwnd, extraBytes);
    }
    void Tab::setItemSize(int x, int y)
    {
        TabCtrl_SetItemSize(m_hwnd, x, y);
    }
    void Tab::setMinTabWidth(int x)
    {
        TabCtrl_SetMinTabWidth(m_hwnd, x);
    }
    void Tab::setPadding(int cx, int cy)
    {
        TabCtrl_SetPadding(m_hwnd, cx, cy);
    }
    void Tab::setToolTips(HWND tooltip)
    {
        TabCtrl_SetToolTips(m_hwnd, tooltip);
    }
    void Tab::setUnicodeFormat(BOOL unicode)
    {
        TabCtrl_SetUnicodeFormat(m_hwnd, unicode);
    }
    Button::Button(HWND parent)
    {
		auto const rcClient = GetClientRect(parent);
		m_hwnd = CreateWindow(
			ClassName,
			L"",
			WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			0, 0, rcClient.right/2, rcClient.bottom/2,
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
    LRESULT Control::sendMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        return SendMessage(m_hwnd, message, wParam, lParam);
    }
    Control::Handle Control::getHandle() const
    {
        return m_hwnd;
    }
    void Controls::Control::setVisible(bool visible)
    {
		ShowWindow(m_hwnd, visible? SW_SHOW : SW_HIDE);
    }
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

    DLLVERSIONINFO GetVersion()
    {
        auto const hInstance = LoadLibrary(L"C:\\Windows\\System32\\ComCtl32.dll");
        if (!hInstance)
            return {};

        auto const getVersionProc = reinterpret_cast<DLLGETVERSIONPROC>(
            GetProcAddress(hInstance, "DllGetVersion"));
        if (!getVersionProc)
        {
            FreeLibrary(hInstance);
            return {};
        }			

        DLLVERSIONINFO info{};
        info.cbSize = sizeof(info);
        auto hr = getVersionProc(&info);
        FreeLibrary(hInstance);
        return info;
    }
    Trackbar::Trackbar(HWND parent, DWORD style, int x, int y, int width, int height)
    {
        m_hwnd = CreateWindowEx(
            0, ClassName, L"",
            WS_CHILD | WS_VISIBLE | style,
            x, y, width, height, parent,
            NULL, gHinst, NULL 
        );
    }

    void Trackbar::setRange(int min, int max)
    {
        sendMessage(TBM_SETRANGE, TRUE, MAKEWPARAM(min, max));
    }

    int Trackbar::getPos()
    {
        return sendMessage(TBM_GETPOS, 0, 0);
    }

    void Trackbar::setPos(bool redraw, int position)
    {
        sendMessage(TBM_SETPOS, redraw, position);
    }

}

static void Demo()
{
    //Create Tab
    Controls::Tab tab{ gHwnd };
    tab.addTab(L"Button");
    tab.addTab(L"ComboBox");
    tab.addTab(L"Date Time Picker");
    tab.addTab(L"Edit Control");
    tab.addTab(L"Progress Bar");

    Controls::Button b(tab.getHandle());
    assert(gHwnd != tab.getHandle());
    TCHAR st[] = L"MyButton";
    b.setText(st);
}

#include <unordered_map>
#include <functional>

template<typename Identifier, typename Function>
class Handler
{
	std::unordered_map<Identifier, std::function<Function>> m_handlers;
public:
	template<typename Handler>
	void add(Identifier id, Handler&& handler)
	{
		m_handlers.emplace(id, std::forward<Handler>(handler));
	}

    void remove(Identifier id)
    {
		m_handlers.erase(id);
    }

	template<typename Identifier, typename ... Args>
	void call(Identifier id, Args&& ... args)
	{
        if (m_handlers.empty())
            return;
		
		auto it = m_handlers.find(id);
		if (it != m_handlers.end())
		{
			it->second(std::forward<Args>(args)...);
		}
	}
};

template<typename Function>
class SingletonHandler
{
    Function handler;
public:
    void add(Function&& handler)
    {
        this->handler = handler;
    }

    void remove()
    {
        handler = {};
    }

    template<typename... Args>
    void call(Args&&... args)
    {
        if (handler)
            handler(std::forward<Args>(args)...);
    }
};

class Button : public Controls::Button
{
    
public:
    static inline Handler<HWND, void(HWND)> OnClickHandlers;
	Button(HWND parent, DWORD style, int x, int y, int width, int height)
		: Controls::Button(parent, style, x, y, width, height)
	{
	}

	Button(HWND parent, DWORD style)
		: Controls::Button(parent, style)
	{
	}
	
	template<typename Handler>
    void onClick(Handler&& handler)
    {
        OnClickHandlers.add(m_hwnd, std::move(handler));
    }

    void onClick()
    {
        OnClickHandlers.remove(m_hwnd);
    }
};

class RadioButton : public Button
{
public:
	RadioButton(HWND parent, LPCTSTR text, int x, int y, int width, int height)
		: Button(parent, static_cast<DWORD>(Controls::Button::Style::RadioButton), x, y, width, height)
	{
        setText(text);
	}
};

class Checkbox : public Button
{
    bool m_checked{};

    void addHandler()
    {
        OnClickHandlers.add(m_hwnd, [this](HWND hwnd)
		{
			m_checked = !m_checked;
			Button_SetCheck(hwnd, m_checked);
		});
    }
	
public:
    Checkbox(HWND parent, LPCTSTR text)
        : Button(parent, static_cast<DWORD>(Controls::Button::Style::Checkbox))
    {
        setText(text);
        addHandler();
    }

	Checkbox(HWND parent, LPCTSTR text, int x, int y, int width, int height)
		: Button(parent, static_cast<DWORD>(Controls::Button::Style::Checkbox), x, y, width, height)
	{
		setText(text);
        addHandler();
	}

    bool isChecked() const
    {
        return m_checked;
    }

    void setCheck(bool check)
    {
        m_checked = check;
        Button::setCheck(check);
    }

	template<typename Handler>
    void onClick(Handler&& handler)
    {
        OnClickHandlers.remove(m_hwnd);
        OnClickHandlers.add(m_hwnd, [handler, this](HWND hwnd) {
            m_checked = !m_checked;
            Button_SetCheck(hwnd, m_checked);
            handler(hwnd);
        });
    }
};



class Groupbox : public Controls::Button
{
public:
    Groupbox(HWND parent, LPCTSTR text)
        : Button(parent, static_cast<DWORD>(Controls::Button::Style::Groupbox))
    {
		setText(text);
    }

    Groupbox(HWND parent, LPCTSTR text, int x, int y, int width, int height)
        : Button(parent, static_cast<DWORD>(Controls::Button::Style::Groupbox), x, y, width, height)
    {
		setText(text);
    }
};

class WindowStyleTooltip : public Controls::Tooltip
{
public:
    WindowStyleTooltip(HWND parent, DWORD style) :
        Controls::Tooltip{ parent, style }
    {

    }

private:
    static inline HWND gItemTip{};

    static WindowStyleTooltip& GetInstance()
    {
        WindowStyleTooltip tooltip{ gHwnd, 0 };
        return tooltip;
    }
public:
    static void OnResize(HWND hwnd, UINT state, int cx, int cy)
    {
        TOOLINFO info
        {
            .cbSize = sizeof(info) - sizeof(void*),
            .hwnd = hwnd,
            .uId = 0,
        };
        GetClientRect(hwnd, &info.rect);
        GetInstance().newToolRect(info);
    }

    static void UpdateTooltip(HWND hwnd, int x, int y)
    {
        gItemTip = GetInstance().hitTest(
            TTHITTESTINFO
            {
                .hwnd = hwnd,
                .pt = POINT{.x = x, .y = y}
            }
        ) ? hwnd : HWND{};
    }

    static void RelayEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        UpdateTooltip(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        GetInstance().relayEvent(
            MSG
            {
                .hwnd = hwnd,
                .message = msg,
                .wParam = wParam,
                .lParam = lParam
            }
        );
    }
};

class WindowStyleCheckbox : public Checkbox
{
    DWORD m_style{};
    LPCTSTR m_text{};
    std::wstring m_description;
    WindowStyleTooltip m_tip;

    void addInfo()
    {
        m_tip.setTitle(Controls::Tooltip::Icon::InfoLarge, m_text);
        TOOLINFO info
        {
            .cbSize = sizeof(info) - sizeof(void*),
            .uFlags = TTF_IDISHWND | TTF_SUBCLASS,
            .hwnd = gHwnd,
            .uId = reinterpret_cast<UINT_PTR>(m_hwnd),
            .hinst = gHinst,
            .lpszText = &m_description[0]
        };
        m_tip.addTool(info);
        m_tip.activate();
    }
public:
    WindowStyleCheckbox(HWND parent, DWORD style, LPCTSTR text, LPCTSTR description)
        : Checkbox(parent, text), m_style{ style }, m_text{ text }, m_description{description}, m_tip{gHwnd, {}}
    {
        addInfo();
    }

    WindowStyleCheckbox(HWND parent, DWORD style, LPCTSTR text, int x, int y, int width, int height, LPCTSTR description)
        : Checkbox(parent, text, x, y, width, height), m_style{ style }, m_description{ description }, m_text{ text }, m_tip{ gHwnd, {} }
    {
        addInfo();
    }

    DWORD getValue() const
    {
        return isChecked() ? m_style : 0;
    }

    friend std::wostream& operator<<(std::wostream& os, WindowStyleCheckbox const& checkbox)
    {
        if (checkbox.isChecked())
            os << checkbox.m_text << L' ';
        return os;
    }

    void flash(int times = 3)
    {
        while (times--)
        {
            setCheck(true);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
            setCheck(false);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
        }
    }		

    auto flashAsync(int times = 3)
    {
        return std::async(
            std::launch::async,
            [this, times]() mutable
            {
                flash();
            }
        );
    }
};

template<typename ValueType>
class DwmAttributeCheckbox : public Checkbox
{
    DWORD const m_attribute{};
    ValueType const m_enableValue;
    ValueType const m_disableValue;
public:
    DwmAttributeCheckbox(HWND parent, LPCTSTR text, int x, int y, int width, int height, DWORD attribute, ValueType enableValue, ValueType disableValue = {})
		: Checkbox(parent, text, x, y, width, height), m_attribute{m_attribute}, m_enableValue{ enableValue }, m_disableValue{disableValue}
	{
        onClick([this]
        {
            if (gCreatedWindow)
            {
                DwmSetWindowAttribute(gCreatedWindow, m_attribute,
                    isChecked() ? &m_enableValue : &m_disableValue, sizeof(ValueType));
            }
        });
	}
};

class Relation
{
public:
    virtual void execute() = 0;
    std::future<void> executeAsync()
    {
        return std::async(
            std::launch::async,
            [this]()
            {
                execute();
            }
        );
    }
};

class EquivalentRelation : public Relation
{
    std::vector<WindowStyleCheckbox*> m_checkbox;
public:
    EquivalentRelation() = default;
    EquivalentRelation(std::vector<WindowStyleCheckbox*> checkbox)
        : m_checkbox{ std::move(checkbox) }
    {
    }
	
    EquivalentRelation& operator+=(WindowStyleCheckbox& checkbox)
    {
        m_checkbox.push_back(&checkbox);
        return *this;
    }

    void execute() override
    {
        int times = 3;
        while (times--)
        {
            for (auto& checkbox : m_checkbox)
                checkbox->setCheck(true);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
            for (auto& checkbox : m_checkbox)
                checkbox->setCheck(false);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
        }
    }

    void setCheck(bool check)
    {
        for (auto& checkbox : m_checkbox)
            checkbox->setCheck(check);
    }
};

class RequirementRelation : public Relation
{
    WindowStyleCheckbox* m_primary;
    std::vector<WindowStyleCheckbox*> m_requirement;
public:
    RequirementRelation(WindowStyleCheckbox& primary) 
        : m_primary{ &primary }
    {
    }
	
    RequirementRelation(WindowStyleCheckbox& primary, std::vector<WindowStyleCheckbox*> requirments)
        : m_primary{ &primary }, m_requirement{ std::move(requirments) }
    {
    }

	RequirementRelation& operator+=(WindowStyleCheckbox& checkbox)
	{
		m_requirement.push_back(&checkbox);
		return *this;
	}

	void execute() override
	{
        throw std::exception{};
	}

};

class Slider : public Controls::Trackbar
{
public:
    static inline Handler<HWND, void()> OnThumbPositionChangeHandlers;

    Slider(HWND parent, bool horizontal, int x, int y, int width, int height)
        : Controls::Trackbar{ parent,
        static_cast<DWORD>(horizontal ? Controls::Trackbar::Style::Horz : Controls::Trackbar::Style::Vert),
        x, y, width, height }
    {
    }
	
	template<typename Handler>
    void onPositionChange(Handler&& handler)
    {
        OnThumbPositionChangeHandlers.add(m_hwnd, std::forward<Handler>(handler));
    }

    void onPositionChange()
    {
        OnThumbPositionChangeHandlers.remove(m_hwnd);
    }

};

class LayeredWindowAttributes
{
    Groupbox m_groupBox;
    Slider m_sliderR;
	Slider m_sliderG;
	Slider m_sliderB;
	Slider m_sliderA;
    Checkbox m_toggleRGBASwicth; //implement a toggleswitch

    constexpr static inline auto SliderMin = 0;
    constexpr static inline auto SliderMax = 255;

    BYTE m_R{};
	BYTE m_G{};
	BYTE m_B{};
    BYTE m_alpha{};

    bool isRGBMode()
    {
        return m_toggleRGBASwicth.isChecked();
    }

    void setLayeredWindow(bool useRGB = true)
    {
        SetLayeredWindowAttributes(gCreatedWindow, RGB(m_R, m_G, m_B), 
            m_alpha, useRGB ? LWA_COLORKEY : LWA_ALPHA);
    }

    void addHandler()
    {
        //add handlers for sliders
        m_sliderR.onPositionChange([this](/*NMTRBTHUMBPOSCHANGING* position*/)
        {
            m_R = static_cast<BYTE>(m_sliderR.getPos());
            if (gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });

        m_sliderG.onPositionChange([this](/*NMTRBTHUMBPOSCHANGING* position*/)
        {
            m_G = static_cast<BYTE>(m_sliderG.getPos());
            if(gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });
        m_sliderB.onPositionChange([this](/*NMTRBTHUMBPOSCHANGING* position*/)
        {
            m_B = static_cast<BYTE>(m_sliderB.getPos());
            if (gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });

        m_sliderA.onPositionChange([this](/*NMTRBTHUMBPOSCHANGING* position*/)
        {
            m_alpha = static_cast<BYTE>(m_sliderA.getPos());
            if (gCreatedWindow && !isRGBMode())
                setLayeredWindow(false);
        });

        m_toggleRGBASwicth.onClick([this](HWND)
        {
            setLayeredWindow(isRGBMode());
        });
    }

    void setRange()
    {
        m_sliderR.setRange(SliderMin, SliderMax);
		m_sliderG.setRange(SliderMin, SliderMax);
		m_sliderB.setRange(SliderMin, SliderMax);
		m_sliderA.setRange(SliderMin, SliderMax);
    }

    void setInitialPosition()
    {
        m_sliderR.setPos(true, SliderMax);
        m_sliderG.setPos(true, SliderMax);
        m_sliderB.setPos(true, SliderMax);
        m_sliderA.setPos(true, SliderMax);

        m_R = SliderMax;
        m_G = SliderMax;
        m_B = SliderMax;
        m_alpha = SliderMax;
    }

    LayeredWindowAttributes(HWND parent, int x, int y)
        : m_groupBox{ parent, L"Layered window attributes", x, y, 100, 600 },
        m_sliderR{ parent, true, x, y + 50, 100, 100 },
        m_sliderG{ parent, true, x, y + 150, 100, 100 },
        m_sliderB{ parent, true, x, y + 250, 100, 100 },
        m_sliderA{ parent, true, x, y + 350, 100, 100 },
        m_toggleRGBASwicth{ parent, L"Use RGB", x, y + 450, 100, 100 }
    {
        SetWindowText(m_sliderR.getHandle(), L"R color");
        addHandler();
        setRange();
        setInitialPosition();
        m_toggleRGBASwicth.setCheck(true);
    }

public:

	
    void setVisible(bool visible = true)
    {
        m_groupBox.setVisible(visible);
        m_sliderR.setVisible(visible);
        m_sliderG.setVisible(visible);
        m_sliderB.setVisible(visible);
        m_sliderA.setVisible(visible);
        m_toggleRGBASwicth.setVisible(visible);
    }

    static LayeredWindowAttributes& GetInstance()
    {
        static LayeredWindowAttributes layeredWindowAttributes{ gHwnd, 1000, 000 };
        return layeredWindowAttributes;
    }

    static void MakeLayeredWindow()
    {
        GetInstance().setLayeredWindow(GetInstance().isRGBMode());
        DWMNCRENDERINGPOLICY ncrp = DWMNCRP_DISABLED;

         //Disable non-client area rendering on the window.
        auto hr = ::DwmSetWindowAttribute(gCreatedWindow,
            DWMWA_NCRENDERING_POLICY,
            &ncrp,
            sizeof(ncrp));

        static std::thread t{ [] {
            while (gCreatedWindow)
            {
                InvalidateRect(
                    gCreatedWindow,
                    NULL,
                    TRUE
                );
                std::this_thread::sleep_for(std::chrono::milliseconds{ 10 });
            }
            }			
        };
    }
};

#include "WindowStyleDetail.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    gHinst = hInstance;
    gNCmdShow = nCmdShow;
    auto info = Controls::GetVersion();
	//Ensure that the common control DLL (ComCtl32.dll) is loaded
    Controls::Init();

    Groupbox windowStyles{ gHwnd, L"Window Styles", 0, 0, 500, 2000 };

    int width = 200;
    int const height = 50;

    int row = 1;
    int x = 20;
	
    //27 window styles
    WindowStyleCheckbox border          { gHwnd,           WS_BORDER,              L"WS_BORDER", x, height * row++, width, height, Window::Styles::Description::border            };
    WindowStyleCheckbox caption         { gHwnd,          WS_CAPTION,             L"WS_CAPTION", x, height * row++, width, height, Window::Styles::Description::caption           };
	WindowStyleCheckbox child           { gHwnd,            WS_CHILD,               L"WS_CHILD", x, height * row++, width, height, Window::Styles::Description::child             };
	WindowStyleCheckbox childWindow     { gHwnd,      WS_CHILDWINDOW,         L"WS_CHILDWINDOW", x, height * row++, width, height, Window::Styles::Description::childWindow       };
	WindowStyleCheckbox clipSiblings    { gHwnd,     WS_CLIPSIBLINGS ,       L"WS_CLIPSIBLINGS", x, height * row++, width, height, Window::Styles::Description::clipSiblings      };
	WindowStyleCheckbox clipChildren    { gHwnd,     WS_CLIPCHILDREN,        L"WS_CLIPCHILDREN", x, height * row++, width, height, Window::Styles::Description::clipChildren      };
	WindowStyleCheckbox disabled        { gHwnd,         WS_DISABLED ,           L"WS_DISABLED", x, height * row++, width, height, Window::Styles::Description::disabled          };
    WindowStyleCheckbox dlgFrame        { gHwnd,         WS_DLGFRAME,            L"WS_DLGFRAME", x, height * row++, width, height, Window::Styles::Description::dlgFrame          };
	WindowStyleCheckbox group           { gHwnd,            WS_GROUP ,              L"WS_GROUP", x, height * row++, width, height, Window::Styles::Description::group             };
	WindowStyleCheckbox hScroll         { gHwnd,          WS_HSCROLL ,            L"WS_HSCROLL", x, height * row++, width, height, Window::Styles::Description::hScroll           };
	WindowStyleCheckbox vScroll         { gHwnd,          WS_VSCROLL ,            L"WS_VSCROLL", x, height * row++, width, height, Window::Styles::Description::vScroll           };
    WindowStyleCheckbox iconic          { gHwnd,           WS_ICONIC ,             L"WS_ICONIC", x, height * row++, width, height, Window::Styles::Description::iconic            };
	WindowStyleCheckbox minimize        { gHwnd,         WS_MINIMIZE,            L"WS_MINIMIZE", x, height * row++, width, height, Window::Styles::Description::minimize          };
	WindowStyleCheckbox maximize        { gHwnd,         WS_MAXIMIZE,            L"WS_MAXIMIZE", x, height * row++, width, height, Window::Styles::Description::maximize          };
	WindowStyleCheckbox maximizeBox     { gHwnd,      WS_MAXIMIZEBOX,         L"WS_MAXIMIZEBOX", x, height * row++, width, height, Window::Styles::Description::maximizeBox       };
	WindowStyleCheckbox minimizeBox     { gHwnd,      WS_MINIMIZEBOX,         L"WS_MINIMIZEBOX", x, height * row++, width, height, Window::Styles::Description::minimizeBox       };
	WindowStyleCheckbox overlapped      { gHwnd,       WS_OVERLAPPED,          L"WS_OVERLAPPED", x, height * row++, width, height, Window::Styles::Description::overlapped        };
	WindowStyleCheckbox overlappedWindow{ gHwnd, WS_OVERLAPPEDWINDOW,    L"WS_OVERLAPPEDWINDOW", x, height * row++, width, height, Window::Styles::Description::overlappedWindow  };
	WindowStyleCheckbox popUp           { gHwnd,            WS_POPUP,               L"WS_POPUP", x, height * row++, width, height, Window::Styles::Description::popUp             };
	WindowStyleCheckbox popUpWindow     { gHwnd,      WS_POPUPWINDOW,         L"WS_POPUPWINDOW", x, height * row++, width, height, Window::Styles::Description::popUpWindow       };
	WindowStyleCheckbox sizeBox         { gHwnd,          WS_SIZEBOX,             L"WS_SIZEBOX", x, height * row++, width, height, Window::Styles::Description::sizeBox           };
	WindowStyleCheckbox sysMenu         { gHwnd,          WS_SYSMENU,             L"WS_SYSMENU", x, height * row++, width, height, Window::Styles::Description::sysMenu           };
	WindowStyleCheckbox tabStop         { gHwnd,          WS_TABSTOP,             L"WS_TABSTOP", x, height * row++, width, height, Window::Styles::Description::tabStop           };
	WindowStyleCheckbox thickFrame      { gHwnd,       WS_THICKFRAME,          L"WS_THICKFRAME", x, height * row++, width, height, Window::Styles::Description::thickFrame        };
    WindowStyleCheckbox tiled           { gHwnd,            WS_TILED,               L"WS_TILED", x, height * row++, width, height, Window::Styles::Description::tiled             };
	WindowStyleCheckbox tiledWindow     { gHwnd,      WS_TILEDWINDOW,         L"WS_TILEDWINDOW", x, height * row++, width, height, Window::Styles::Description::tiledWindow       };
	WindowStyleCheckbox visible         { gHwnd,          WS_VISIBLE,             L"WS_VISIBLE", x, height * row++, width, height, Window::Styles::Description::visible           };
	

	//Extended Styles
    Groupbox extendedStyles{gHwnd, L"Extended Styles", 500, 0, 500, 2000 };
    x = 500;
    row = 1;
    width += 100;
	WindowStyleCheckbox acceptFiles         { gHwnd,        WS_EX_ACCEPTFILES,      L"WS_EX_ACCEPTFILES", x, height * row++, width, height ,Window::ExtendedStyles::Description::acceptFiles        };
	WindowStyleCheckbox appWindow           { gHwnd,          WS_EX_APPWINDOW,        L"WS_EX_APPWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::appWindow          };
	WindowStyleCheckbox clientEdge          { gHwnd,         WS_EX_CLIENTEDGE,       L"WS_EX_CLIENTEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::clientEdge         };
	WindowStyleCheckbox composited          { gHwnd,          WS_EX_COMPOSITED,       L"WS_EX_COMPOSITED", x, height * row++, width, height,Window::ExtendedStyles::Description::composited          };
	WindowStyleCheckbox contextHelp         { gHwnd,        WS_EX_CONTEXTHELP,      L"WS_EX_CONTEXTHELP", x, height * row++, width, height ,Window::ExtendedStyles::Description::contextHelp        };
	WindowStyleCheckbox controlParent       { gHwnd,      WS_EX_CONTROLPARENT,    L"WS_EX_CONTROLPARENT", x, height * row++, width, height ,Window::ExtendedStyles::Description::controlParent      };
	WindowStyleCheckbox dlgModalFrame       { gHwnd,      WS_EX_DLGMODALFRAME,    L"WS_EX_DLGMODALFRAME", x, height * row++, width, height ,Window::ExtendedStyles::Description::dlgModalFrame      };
	WindowStyleCheckbox layered             { gHwnd,            WS_EX_LAYERED,          L"WS_EX_LAYERED", x, height * row++, width, height ,Window::ExtendedStyles::Description::layered            };
	WindowStyleCheckbox layoutRTL           { gHwnd,           WS_EX_LAYOUTRTL,        L"WS_EX_LAYOUTRTL", x, height * row++, width, height,Window::ExtendedStyles::Description::layoutRTL           };
	WindowStyleCheckbox left                { gHwnd,               WS_EX_LEFT,             L"WS_EX_LEFT", x, height * row++, width, height ,Window::ExtendedStyles::Description::left               };
	WindowStyleCheckbox leftScrollBar       { gHwnd,      WS_EX_LEFTSCROLLBAR,    L"WS_EX_LEFTSCROLLBAR", x, height * row++, width, height ,Window::ExtendedStyles::Description::leftScrollBar      };
	WindowStyleCheckbox leftToRight         { gHwnd,        WS_EX_LTRREADING,       L"WS_EX_LTRREADING", x, height * row++, width, height  ,Window::ExtendedStyles::Description::leftToRight         };
    WindowStyleCheckbox mdiChild            { gHwnd,           WS_EX_MDICHILD,         L"WS_EX_MDICHILD", x, height * row++, width, height ,Window::ExtendedStyles::Description::mdiChild           };
	WindowStyleCheckbox noActivate          { gHwnd,         WS_EX_NOACTIVATE,       L"WS_EX_NOACTIVATE", x, height * row++, width, height ,Window::ExtendedStyles::Description::noActivate         };
	WindowStyleCheckbox noInheritLayout     { gHwnd,    WS_EX_NOINHERITLAYOUT,  L"WS_EX_NOINHERITLAYOUT", x, height * row++, width, height ,Window::ExtendedStyles::Description::noInheritLayout    };
	WindowStyleCheckbox noParentNotify      { gHwnd,     WS_EX_NOPARENTNOTIFY,   L"WS_EX_NOPARENTNOTIFY", x, height * row++, width, height ,Window::ExtendedStyles::Description::noParentNotify     };
    WindowStyleCheckbox noRedirectionBitmap { gHwnd,WS_EX_NOREDIRECTIONBITMAP,   L"WS_EX_NOPARENTNOTIFY", x, height * row++, width, height ,Window::ExtendedStyles::Description::noRedirectionBitmap  };
    WindowStyleCheckbox exOverlappedWindow  { gHwnd, WS_EX_OVERLAPPEDWINDOW, L"WS_EX_OVERLAPPEDWINDOW", x, height * row++, width, height   ,Window::ExtendedStyles::Description::overlappedWindow };
	WindowStyleCheckbox paletteWindow       { gHwnd,      WS_EX_PALETTEWINDOW,    L"WS_EX_PALETTEWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::paletteWindow      };
	WindowStyleCheckbox right               { gHwnd,              WS_EX_RIGHT,            L"WS_EX_RIGHT", x, height * row++, width, height ,Window::ExtendedStyles::Description::right              };
	WindowStyleCheckbox rightScrollBar      { gHwnd,     WS_EX_RIGHTSCROLLBAR,   L"WS_EX_RIGHTSCROLLBAR", x, height * row++, width, height ,Window::ExtendedStyles::Description::rightScrollBar     };
	WindowStyleCheckbox rightToLeft         { gHwnd,        WS_EX_RTLREADING,       L"WS_EX_RTLREADING", x, height * row++, width, height  ,Window::ExtendedStyles::Description::rightToLeft         };
	WindowStyleCheckbox staticEdge          { gHwnd,         WS_EX_STATICEDGE,       L"WS_EX_STATICEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::staticEdge         };
	WindowStyleCheckbox toolWindow          { gHwnd,         WS_EX_TOOLWINDOW,       L"WS_EX_TOOLWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::toolWindow         };
	WindowStyleCheckbox topMost             { gHwnd,            WS_EX_TOPMOST,          L"WS_EX_TOPMOST", x, height * row++, width, height ,Window::ExtendedStyles::Description::topMost            };
	WindowStyleCheckbox transparent         { gHwnd,        WS_EX_TRANSPARENT,      L"WS_EX_TRANSPARENT", x, height * row++, width, height ,Window::ExtendedStyles::Description::transparent        };
	WindowStyleCheckbox windowEdge          { gHwnd,         WS_EX_WINDOWEDGE,       L"WS_EX_WINDOWEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::windowEdge         };
    layered.onClick([&layered](HWND)
    {
		//make RGB and transparency slider
        LayeredWindowAttributes::GetInstance().setVisible(layered.isChecked());
    });

    x = 1500;
    row = 1;
	//DWM attributes
	Groupbox dwmAttributes          { gHwnd, L"DWM Attributes", x, 0, 500, 1000 };
    Checkbox ncRendering            { gHwnd, L"DWM NCRendering", x, height * row++, width, height };
	Checkbox transition             {gHwnd, L"Transition", x, height * row++, width, height};
	Checkbox allowNCPaint           {gHwnd, L"Allow NC paint", x, height * row++, width, height};
	Checkbox ncRightToLeftLayout    { gHwnd, L"NC Right to Left layout", x, height * row++, width, height };
	Checkbox forceIconicPresentation{gHwnd, L"Force iconic representation", x, height * row++, width, height};
	Checkbox hasIconicBitmap        {gHwnd, L"Has iconic bitmap", x, height * row++, width, height};
    RadioButton flip3D[]
    {
        RadioButton{gHwnd, L"DWMFLIP3D_DEFAULT",        x + 50, height * row++, width, height},
        RadioButton{gHwnd, L"DWMFLIP3D_EXCLUDEBELOW",   x + 50, height * row++, width, height},
        RadioButton{gHwnd, L"DWMFLIP3D_EXCLUDEABOVE",   x + 50, height * row++, width, height},
    };
	Checkbox disallowPeek           {gHwnd, L"Disallow peek", x, height * row++, width, height};
	Checkbox excludedFromPeek       {gHwnd, L"Excluded from peek", x, height * row++, width, height};
	Checkbox dwmCloak               {gHwnd, L"DWM Cloak", x, height * row++, width, height};
	Checkbox freezeRepresentation   {gHwnd, L"Freeze representation", x, height * row++, width, height};
    //Windows 11 attributes
	Checkbox useHostBackdropBrush   {gHwnd, L"Use host backdrop brush", x, height * row++, width, height};
	Checkbox useImmersiveDarkMode   {gHwnd, L"Use immersive dark mode", x, height * row++, width, height};
	Checkbox windowCornerPreference {gHwnd, L"Window corner preference", x, height * row++, width, height};
	Checkbox borderColor            {gHwnd, L"Border color", x, height * row++, width, height};
	Checkbox captionColor           {gHwnd, L"Caption color", x, height * row++, width, height};
	
	

    //Create window
    Button createButton{ gHwnd, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 600, width, height};
    createButton.setText(L"Create window");
    createButton.onClick([&](HWND)
    {
		//Create window
        static bool registered = false;
		constexpr auto className = L"WindowStyleTest";
        if (!registered)
        {
            WNDCLASSEXW wcex{};
            wcex.cbSize = sizeof(WNDCLASSEX);
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = WndProc2;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = 0;
            wcex.hInstance = gHinst;
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszClassName = className;
            wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
			RegisterClassExW(&wcex);
			registered = true;
        }

        //Get selected window styles
		DWORD const style = 
            border          .getValue()|
            caption         .getValue()|
            child           .getValue()|
            childWindow     .getValue()|
            clipSiblings    .getValue()|
            clipChildren    .getValue()|
            disabled        .getValue()|
            dlgFrame        .getValue()|
            group           .getValue()|
            hScroll         .getValue()|
            vScroll         .getValue()|
            iconic          .getValue()|
            minimize        .getValue()|
            maximize        .getValue()|
            maximizeBox     .getValue()|
            minimizeBox     .getValue()|
            overlapped      .getValue()|
            overlappedWindow.getValue()|
            popUp           .getValue()|
            popUpWindow     .getValue()|
            sizeBox         .getValue()|
            sysMenu         .getValue()|
            tabStop         .getValue()|
            thickFrame      .getValue()|
            tiled           .getValue()|
            tiledWindow     .getValue()|
            visible         .getValue();
		
		//Get extended styles
		DWORD const extendedStyle = 
            acceptFiles         .getValue()|
            appWindow   	    .getValue()|
            clientEdge          .getValue()|
            composited          .getValue()|
            contextHelp         .getValue()|
            controlParent       .getValue()|
            dlgModalFrame       .getValue()|
            layered             .getValue()|
            layoutRTL           .getValue()|
            left                .getValue()|
            leftScrollBar       .getValue()|   
            leftToRight         .getValue()|
            mdiChild            .getValue()|
            noActivate          .getValue()|
            noInheritLayout     .getValue()|   
            noParentNotify      .getValue()|   
            noRedirectionBitmap .getValue()|
            exOverlappedWindow  .getValue()|     
            paletteWindow       .getValue()| 
            right               .getValue()|
            rightScrollBar      .getValue()|
            rightToLeft         .getValue()|
            staticEdge          .getValue()|
            toolWindow          .getValue()|
            topMost             .getValue()|
            transparent         .getValue()|
            windowEdge          .getValue();

        //Get windows title
        std::wstringstream os;
        os << border
            << caption
            << child
            << childWindow
            << clipSiblings
            << clipChildren
            << disabled
            << dlgFrame
            << group
            << hScroll
            << vScroll
            << iconic
            << minimize
            << maximize
            << maximizeBox
            << minimizeBox
            << overlapped
            << overlappedWindow
            << popUp
            << popUpWindow
            << sizeBox
            << sysMenu
            << tabStop
            << thickFrame
            << tiled
            << tiledWindow
            << visible
            << acceptFiles
            << appWindow
            << clientEdge
            << composited
            << contextHelp
            << controlParent
            << dlgModalFrame
            << layered
            << layoutRTL
            << left
            << leftScrollBar
            << leftToRight
            << mdiChild
            << noActivate
            << noInheritLayout
            << noParentNotify
            << noRedirectionBitmap
            << exOverlappedWindow
            << paletteWindow
            << right
            << rightScrollBar
            << rightToLeft
            << staticEdge
            << toolWindow
            << topMost
            << transparent
            << windowEdge;

		
			
		gCreatedWindow = CreateWindowEx(extendedStyle, className, os.str().c_str(), 
            style, 1000, 1000, 800, 600, nullptr, nullptr, gHinst, nullptr);
	

        SetWindowLongPtr(gCreatedWindow, GWL_STYLE, style);
        SetWindowLongPtr(gCreatedWindow, GWL_EXSTYLE, extendedStyle);

        if (layered.isChecked())
            LayeredWindowAttributes::MakeLayeredWindow();

		if (gCreatedWindow)
			ShowWindow(gCreatedWindow, SW_SHOW);
        UpdateWindow(gCreatedWindow);
			
		

        OutputDebugString(L"Create window");
    });

	//Window style assistant
	Checkbox assist{ gHwnd, L"Window style assist", 1000, 700, width, height };
    assist.onClick([&](HWND)
    {
        static std::vector<std::future<void>> flashing;
        flashing.clear();
        if (assist.isChecked())
        {
	        //add handlers
            OutputDebugString(L"Should add handlers\n");
            
        }
        else
        {
	        //remove handlers
            OutputDebugString(L"Should remove handlers\n");
        }
    });
	

	//Close window
    Button closeButton{ gHwnd, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 850, width, height };
    closeButton.setText(L"Close window");
    closeButton.onClick([](HWND)
        {
            if (gCreatedWindow)
            {
				DestroyWindow(gCreatedWindow);
                OutputDebugString(L"Close window");
            }
        });

    
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    HACCEL hAccelTable = LoadAccelerators(gHinst, MAKEINTRESOURCE(IDC_CORE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
    switch (message)
    {
        case WM_COMMAND:
            {
			    //switch(wPa)
                int wmId = LOWORD(wParam);
                // Parse the menu selections:
                switch (wmId)
                {
                    case IDM_ABOUT:
                        DialogBox(gHinst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                        break;
                    case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    case Controls::Button::Message::Clicked:   Button::OnClickHandlers.call(HWND(lParam), HWND(lParam)); break;
                    case Controls::Button::Message::Pushed:
						OutputDebugString(L"Button pushed");
						break;
                    case Controls::Button::Message::HotItemChange:
	                    OutputDebugString(L"Button hot item change");
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                // TODO: Add any drawing code that uses hdc here...
                EndPaint(hWnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_HSCROLL:
            if (LOWORD(wParam) == TB_THUMBTRACK)
            {
                Slider::OnThumbPositionChangeHandlers.call(HWND(lParam));
            }
            break;
        case WM_NOTIFY:
            return DefWindowProc(hWnd, message, wParam, lParam);
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}

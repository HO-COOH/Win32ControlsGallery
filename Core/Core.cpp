// Core.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Core.h"

HINSTANCE gHinst;
HWND gHwnd;
int gNCmdShow;
#define MAX_LOADSTRING 100

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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

    //
    //   FUNCTION: InitInstance(HINSTANCE, int)
    //
    //   PURPOSE: Saves instance handle and creates main window
    //
    //   COMMENTS:
    //
    //        In this function, we save the instance handle in a global variable and
    //        create and display the main program window.
    //
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
        return strlen(str);
    }

    DWORD StringLength(LPCWSTR str)
    {
        return wcslen(str);
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
        TabCtrl_GetExtendedStyle(m_hwnd);
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
		TabCtrl_HitTest(m_hwnd, &info);
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
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    gHinst = hInstance;
    gNCmdShow = nCmdShow;
	//Ensure that the common control DLL (ComCtl32.dll) is loaded
    Controls::Init();

	//Create Tab
    Controls::Tab tab{ gHwnd };
    tab.addTab(L"Button");
    tab.addTab(L"ComboBox");
    tab.addTab(L"Date Time Picker");
    tab.addTab(L"Edit Control");
    tab.addTab(L"Progress Bar");

    
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



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
            {
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
        case WM_NOTIFY:
            switch (reinterpret_cast<LPNMHDR>(lParam)->code)
            {
                case TCN_SELCHANGE:
                    OutputDebugString(L"TCN_SELCHANGE");
                    break;
                default:
                    break;
            }
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

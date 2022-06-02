#include "pch.h"
#include <UI.Window.hpp>
#include "Gallery.Pages.WindowPage.ExampleWindow.h"
#include "Gallery.MainWindow.h"
#include "Gallery.SplashScreen.h"
#include "Resource.h"
#include "Gallery.Tabs.h"
#include "Gallery.Pages.WindowPage.Page.h"
#include "Gallery.Pages.ButtonPage.Page.h"
#include "Gallery.Pages.ShellPage.Page.h"
#include "Gallery.Pages.WinUIPage.Page.h"


using namespace Gallery;



//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HINSTANCE gHinst;
HWND gHwnd;
Gallery::Pages::WindowPage::ExampleWindow gCreatedWindow;
static int gNCmdShow;
#define MAX_LOADSTRING 100

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text




BOOL InitInstance(int nCmdShow)
{

	gHwnd = MainWindow::Create(szTitle, WS_OVERLAPPEDWINDOW,
		500, 500, 2000, 1500, nullptr, nullptr, gHinst, nullptr);


	if (!gHwnd)
	{
		return FALSE;
	}

	std::shared_ptr<SplashScreen> splashScreen;
	if (RECT mainWindowRect{}; GetWindowRect(gHwnd, &mainWindowRect))
	{
		splashScreen = std::make_shared<SplashScreen>(mainWindowRect.left + 9, mainWindowRect.top, mainWindowRect.right - mainWindowRect.left - 18, mainWindowRect.bottom - mainWindowRect.top - 9, 500);
	}
	else
	{
		splashScreen = std::make_shared<SplashScreen>(CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 500);
	}

	splashScreen->setImage(Graphics::Bitmap{
		/*Graphics::Image{L"splash.png", Graphics::Image::Type::Bitmap, 200,200,LR_LOADFROMFILE}*/
		L"splash.png"
		});
	splashScreen->onFinish([] {
		ShowWindow(gHwnd, SW_SHOWNOACTIVATE);
		});

	splashScreen->show();
	UpdateWindow(gHwnd);
	return TRUE;
}


void InitWindow()
{
	// Initialize global strings
	LoadStringW(gHinst, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	MainWindow::Register(gHinst);
	// Perform application initialization:
	if (!InitInstance(gNCmdShow))
	{
		return;
	}
}




void Init()
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	InitWindow();
	Controls::Init();


}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    CoInitialize(nullptr);
    gHinst = hInstance;
    gNCmdShow = nCmdShow;
    auto info = Controls::GetVersion();

    //Ensure that the common control DLL (ComCtl32.dll) is loaded
    Init();


    Tabs tab{ gHwnd };
    tab += std::make_unique<Gallery::Pages::WindowPage::Page>(tab.getContainerWindow());
    tab += std::make_unique<Gallery::Pages::ButtonPage::Page>(tab.getContainerWindow());
	tab += std::make_unique<Gallery::Pages::ShellPage::Page>(tab.getContainerWindow());
	tab += std::make_unique<Gallery::Pages::WinUIPage::Page>(tab.getContainerWindow());
	tab.show();
	

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
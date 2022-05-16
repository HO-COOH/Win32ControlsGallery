// Core.cpp : Defines the entry point for the application.
//
#include "pch.h"
#include "framework.h"
#include "Core.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <future>
#include <dwmapi.h>
#include <Uxtheme.h>
#include <array>
#include "Gallery.SplashScreen.h"
#include "Gallery.MainWindow.h"
#include "Gallery.Pages.WindowPage.WindowStyleCheckbox.h"
#include "Gallery.Slider.h"
#include "Gallery.Pages.WindowPage.DwmAttributeCheckbox.h"
#include "Gallery.Pages.WindowPage.DwmAttributeRadioButton.h"
#include "Gallery.Pages.WindowPage.ExampleWindow.h"

using namespace Gallery;
using namespace Gallery::Pages::WindowPage;


#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HINSTANCE gHinst;
HWND gHwnd;
static HWND gCreatedWindow;
static int gNCmdShow;
#define MAX_LOADSTRING 100

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text




BOOL InitInstance(int nCmdShow)
{

	gHwnd = MainWindow::Create(szTitle, WS_OVERLAPPEDWINDOW,
		500, 500, 2000, 1000, nullptr, nullptr, gHinst, nullptr);


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
    auto v = Controls::GetVersion();
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
        m_sliderR.onPositionChange([this]()
        {
            m_R = static_cast<BYTE>(m_sliderR.getPos());
            if (gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });

        m_sliderG.onPositionChange([this]()
        {
            m_G = static_cast<BYTE>(m_sliderG.getPos());
            if(gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });
        m_sliderB.onPositionChange([this]()
        {
            m_B = static_cast<BYTE>(m_sliderB.getPos());
            if (gCreatedWindow && isRGBMode())
                setLayeredWindow(true);
        });

        m_sliderA.onPositionChange([this]()
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
        //auto hr = ::DwmSetWindowAttribute(gCreatedWindow,
        //    DWMWA_NCRENDERING_POLICY,
        //    &ncrp,
        //    sizeof(ncrp));
#pragma warning(disable : 4995)
        //DwmEnableComposition(DWM_EC_DISABLECOMPOSITION);

        //SetWindowTheme(gCreatedWindow, L" ", L" ");
		

        DWM_BLURBEHIND blur
        {
            .dwFlags = DWM_BB_ENABLE,
            .fEnable = true,
            .hRgnBlur = 0,
            .fTransitionOnMaximized = FALSE
        };
		DwmEnableBlurBehindWindow(gCreatedWindow, &blur);

        BOOL const iconic = TRUE;
        BOOL const hasIcon = TRUE;
		DwmSetWindowAttribute(gCreatedWindow, DWMWA_FORCE_ICONIC_REPRESENTATION, &iconic, sizeof(iconic));
		DwmSetWindowAttribute(gCreatedWindow, DWMWA_HAS_ICONIC_BITMAP, &hasIcon, sizeof(hasIcon));

        static std::thread t{ [] {
            while (gCreatedWindow)
            {
                InvalidateRect(
                    gCreatedWindow,
                    NULL,
                    FALSE
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
    CoInitialize(nullptr);
    gHinst = hInstance;
    gNCmdShow = nCmdShow;
    auto info = Controls::GetVersion();
	
	//Ensure that the common control DLL (ComCtl32.dll) is loaded
    Init();

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

    //DWM attributes
    x = 1500;
    row = 1;
	Groupbox dwmAttributes                      { gHwnd, L"DWM Attributes", x, 0, 500, 1000 };
    DwmAttributeCheckbox ncRendering            { gHwnd, L"DWM NCRendering", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_NCRENDERING_POLICY, DWMNCRENDERINGPOLICY::DWMNCRP_ENABLED, DWMNCRENDERINGPOLICY::DWMNCRP_DISABLED };
	DwmAttributeCheckbox transition             {gHwnd, L"Transition", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_TRANSITIONS_FORCEDISABLED, FALSE, TRUE};
	DwmAttributeCheckbox allowNCPaint           {gHwnd, L"Allow NC paint", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_ALLOW_NCPAINT, TRUE, FALSE};
	DwmAttributeCheckbox ncRightToLeftLayout    { gHwnd, L"NC Right to Left layout", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_NONCLIENT_RTL_LAYOUT, TRUE, FALSE };
	DwmAttributeCheckbox forceIconicPresentation{gHwnd, L"Force iconic representation", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_FORCE_ICONIC_REPRESENTATION, TRUE, FALSE};
	DwmAttributeCheckbox hasIconicBitmap        {gHwnd, L"Has iconic bitmap", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_HAS_ICONIC_BITMAP, TRUE, FALSE};
    std::array flip3D
    {
        DwmAttributeRadioButton{gHwnd, L"DWMFLIP3D_DEFAULT",        x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_DEFAULT},
        DwmAttributeRadioButton{gHwnd, L"DWMFLIP3D_EXCLUDEBELOW",   x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_EXCLUDEBELOW},
        DwmAttributeRadioButton{gHwnd, L"DWMFLIP3D_EXCLUDEABOVE",   x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_EXCLUDEABOVE},
    };
	DwmAttributeCheckbox disallowPeek           {gHwnd, L"Disallow peek", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_DISALLOW_PEEK, TRUE, FALSE};
	DwmAttributeCheckbox excludedFromPeek       {gHwnd, L"Excluded from peek", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_EXCLUDED_FROM_PEEK, TRUE, FALSE};
	DwmAttributeCheckbox dwmCloak               {gHwnd, L"DWM Cloak", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_CLOAK, TRUE, FALSE};
	DwmAttributeCheckbox freezeRepresentation   {gHwnd, L"Freeze representation", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_FREEZE_REPRESENTATION, TRUE, FALSE};
    //Windows 11 attributes
    DwmAttributeCheckbox useHostBackdropBrush   {gHwnd, L"Use host backdrop brush", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_USE_HOSTBACKDROPBRUSH, TRUE, FALSE};
    DwmAttributeCheckbox useImmersiveDarkMode   {gHwnd, L"Use immersive dark mode", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE, TRUE, FALSE};
    std::array windowCornerPreference
    {
        DwmAttributeRadioButton{gHwnd, L"DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT},
		DwmAttributeRadioButton{gHwnd, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_DONOTROUND", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND},
        DwmAttributeRadioButton{gHwnd, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_ROUND", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND},
		DwmAttributeRadioButton{gHwnd, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_ROUNDSMALL", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL},
    };
	Checkbox borderColor            {gHwnd, L"Border color", x, height * row++, width, height};
	Checkbox captionColor           {gHwnd, L"Caption color", x, height * row++, width, height};
	
	

    //Create window
    ButtonEx createButton{ gHwnd, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 600, width, height};
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
            wcex.lpfnWndProc = ExampleWindow::WndProc;
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

		
		gCreatedWindow = CreateWindowExW(extendedStyle, className, os.str().c_str(), 
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
    ButtonEx closeButton{ gHwnd, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 850, width, height };
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

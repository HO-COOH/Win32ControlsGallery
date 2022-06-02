// Core.cpp : Defines the entry point for the application.
//
#include "pch.h"
#include "framework.h"
#include "Gallery.Pages.WindowPage.Page.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <future>
#include <dwmapi.h>
#include <Uxtheme.h>
#include "Gallery.Tabs.h"
#include <UI.Window.hpp>
#include "WindowStyleDetail.h"

using namespace Gallery;
using namespace Gallery::Pages::WindowPage;

extern ExampleWindow gCreatedWindow;

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

    static LayeredWindowAttributes& GetInstance(HWND parent)
    {
        static LayeredWindowAttributes layeredWindowAttributes{ parent, 1000, 000 };
        return layeredWindowAttributes;
    }

    static void MakeLayeredWindow(HWND parent)
    {
        GetInstance(parent).setLayeredWindow(GetInstance(parent).isRGBMode());

		UI::Dwm::EnableBlurBehindWindow(gCreatedWindow, DWM_BLURBEHIND
        {
            .dwFlags = DWM_BB_ENABLE,
            .fEnable = true,
            .hRgnBlur = 0,
            .fTransitionOnMaximized = FALSE
        });

		UI::Dwm::SetWindowAttribute(gCreatedWindow, DWMWA_FORCE_ICONIC_REPRESENTATION, TRUE);
		UI::Dwm::SetWindowAttribute(gCreatedWindow, DWMWA_HAS_ICONIC_BITMAP, TRUE);

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



Gallery::Pages::WindowPage::Page::Page(HWND hwnd, int width, int height, int row, int x) :
    TabPageBase{hwnd, L"Window"},
	
	windowStyles{m_container, L"Window Styles", 0, 0, 500, 2000},
    border{ m_container,   WS_BORDER, L"WS_BORDER", x, height * row++, width, height, Window::Styles::Description::border },
	caption{m_container, WS_CAPTION, L"WS_CAPTION", x, height * row++, width, height, Window::Styles::Description::caption },
    child{ m_container,            WS_CHILD,               L"WS_CHILD", x, height * row++, width, height, Window::Styles::Description::child },
    childWindow{ m_container,      WS_CHILDWINDOW,         L"WS_CHILDWINDOW", x, height * row++, width, height, Window::Styles::Description::childWindow },
    clipSiblings{ m_container,     WS_CLIPSIBLINGS ,       L"WS_CLIPSIBLINGS", x, height * row++, width, height, Window::Styles::Description::clipSiblings },
    clipChildren{ m_container,     WS_CLIPCHILDREN,        L"WS_CLIPCHILDREN", x, height * row++, width, height, Window::Styles::Description::clipChildren },
    disabled{ m_container,         WS_DISABLED ,           L"WS_DISABLED", x, height * row++, width, height, Window::Styles::Description::disabled },
    dlgFrame{ m_container,         WS_DLGFRAME,            L"WS_DLGFRAME", x, height * row++, width, height, Window::Styles::Description::dlgFrame },
    group{ m_container,            WS_GROUP ,              L"WS_GROUP", x, height * row++, width, height, Window::Styles::Description::group },
    hScroll{ m_container,          WS_HSCROLL ,            L"WS_HSCROLL", x, height * row++, width, height, Window::Styles::Description::hScroll },
    vScroll{ m_container,          WS_VSCROLL ,            L"WS_VSCROLL", x, height * row++, width, height, Window::Styles::Description::vScroll },
    iconic{ m_container,           WS_ICONIC ,             L"WS_ICONIC", x, height * row++, width, height, Window::Styles::Description::iconic },
    minimize{ m_container,         WS_MINIMIZE,            L"WS_MINIMIZE", x, height * row++, width, height, Window::Styles::Description::minimize },
    maximize{ m_container,         WS_MAXIMIZE,            L"WS_MAXIMIZE", x, height * row++, width, height, Window::Styles::Description::maximize },
    maximizeBox{ m_container,      WS_MAXIMIZEBOX,         L"WS_MAXIMIZEBOX", x, height * row++, width, height, Window::Styles::Description::maximizeBox },
    minimizeBox{ m_container,      WS_MINIMIZEBOX,         L"WS_MINIMIZEBOX", x, height * row++, width, height, Window::Styles::Description::minimizeBox },
    overlapped{ m_container,       WS_OVERLAPPED,          L"WS_OVERLAPPED", x, height * row++, width, height, Window::Styles::Description::overlapped },
    overlappedWindow{ m_container, WS_OVERLAPPEDWINDOW,    L"WS_OVERLAPPEDWINDOW", x, height * row++, width, height, Window::Styles::Description::overlappedWindow },
    popUp{ m_container,            WS_POPUP,               L"WS_POPUP", x, height * row++, width, height, Window::Styles::Description::popUp },
    popUpWindow{ m_container,      WS_POPUPWINDOW,         L"WS_POPUPWINDOW", x, height * row++, width, height, Window::Styles::Description::popUpWindow },
    sizeBox{ m_container,          WS_SIZEBOX,             L"WS_SIZEBOX", x, height * row++, width, height, Window::Styles::Description::sizeBox },
    sysMenu{ m_container,          WS_SYSMENU,             L"WS_SYSMENU", x, height * row++, width, height, Window::Styles::Description::sysMenu },
    tabStop{ m_container,          WS_TABSTOP,             L"WS_TABSTOP", x, height * row++, width, height, Window::Styles::Description::tabStop },
    thickFrame{ m_container,       WS_THICKFRAME,          L"WS_THICKFRAME", x, height * row++, width, height, Window::Styles::Description::thickFrame },
    tiled{ m_container,            WS_TILED,               L"WS_TILED", x, height * row++, width, height, Window::Styles::Description::tiled },
    tiledWindow{ m_container,      WS_TILEDWINDOW,         L"WS_TILEDWINDOW", x, height * row++, width, height, Window::Styles::Description::tiledWindow },
    visible{ m_container,          WS_VISIBLE,             L"WS_VISIBLE", x, height * row++, width, height, Window::Styles::Description::visible },

    extendedStyles{ m_container, L"Extended Styles", 500, 0, 500, 2000 },
    acceptFiles{ m_container,        WS_EX_ACCEPTFILES,      L"WS_EX_ACCEPTFILES", (x = 500), height * (row = 2, 1), width += 100, height ,Window::ExtendedStyles::Description::acceptFiles },
    appWindow{ m_container,          WS_EX_APPWINDOW,        L"WS_EX_APPWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::appWindow },
    clientEdge{ m_container,         WS_EX_CLIENTEDGE,       L"WS_EX_CLIENTEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::clientEdge },
    composited{ m_container,          WS_EX_COMPOSITED,       L"WS_EX_COMPOSITED", x, height * row++, width, height,Window::ExtendedStyles::Description::composited },
    contextHelp         { m_container,        WS_EX_CONTEXTHELP,      L"WS_EX_CONTEXTHELP", x, height * row++, width, height ,Window::ExtendedStyles::Description::contextHelp        },
    controlParent       { m_container,      WS_EX_CONTROLPARENT,    L"WS_EX_CONTROLPARENT", x, height * row++, width, height ,Window::ExtendedStyles::Description::controlParent      },
    dlgModalFrame       { m_container,      WS_EX_DLGMODALFRAME,    L"WS_EX_DLGMODALFRAME", x, height * row++, width, height ,Window::ExtendedStyles::Description::dlgModalFrame      },
    layered             { m_container,            WS_EX_LAYERED,          L"WS_EX_LAYERED", x, height * row++, width, height ,Window::ExtendedStyles::Description::layered            },
    layoutRTL{ m_container,           WS_EX_LAYOUTRTL,        L"WS_EX_LAYOUTRTL", x, height * row++, width, height,Window::ExtendedStyles::Description::layoutRTL },
    left                { m_container,               WS_EX_LEFT,             L"WS_EX_LEFT", x, height * row++, width, height ,Window::ExtendedStyles::Description::left               },
    leftScrollBar       { m_container,      WS_EX_LEFTSCROLLBAR,    L"WS_EX_LEFTSCROLLBAR", x, height * row++, width, height ,Window::ExtendedStyles::Description::leftScrollBar      },
    leftToRight{ m_container,        WS_EX_LTRREADING,       L"WS_EX_LTRREADING", x, height * row++, width, height  ,Window::ExtendedStyles::Description::leftToRight },
    mdiChild            { m_container,           WS_EX_MDICHILD,         L"WS_EX_MDICHILD", x, height * row++, width, height ,Window::ExtendedStyles::Description::mdiChild           },
    noActivate          { m_container,         WS_EX_NOACTIVATE,       L"WS_EX_NOACTIVATE", x, height * row++, width, height ,Window::ExtendedStyles::Description::noActivate         },
    noInheritLayout     { m_container,    WS_EX_NOINHERITLAYOUT,  L"WS_EX_NOINHERITLAYOUT", x, height * row++, width, height ,Window::ExtendedStyles::Description::noInheritLayout    },
    noParentNotify      { m_container,     WS_EX_NOPARENTNOTIFY,   L"WS_EX_NOPARENTNOTIFY", x, height * row++, width, height ,Window::ExtendedStyles::Description::noParentNotify     },
    noRedirectionBitmap{ m_container,WS_EX_NOREDIRECTIONBITMAP,   L"WS_EX_NOPARENTNOTIFY", x, height * row++, width, height ,Window::ExtendedStyles::Description::noRedirectionBitmap },
    exOverlappedWindow  { m_container, WS_EX_OVERLAPPEDWINDOW, L"WS_EX_OVERLAPPEDWINDOW", x, height * row++, width, height   ,Window::ExtendedStyles::Description::overlappedWindow },
    paletteWindow       { m_container,      WS_EX_PALETTEWINDOW,    L"WS_EX_PALETTEWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::paletteWindow      },
    right               { m_container,              WS_EX_RIGHT,            L"WS_EX_RIGHT", x, height * row++, width, height ,Window::ExtendedStyles::Description::right              },
    rightScrollBar      { m_container,     WS_EX_RIGHTSCROLLBAR,   L"WS_EX_RIGHTSCROLLBAR", x, height * row++, width, height ,Window::ExtendedStyles::Description::rightScrollBar     },
    rightToLeft{ m_container,        WS_EX_RTLREADING,       L"WS_EX_RTLREADING", x, height * row++, width, height  ,Window::ExtendedStyles::Description::rightToLeft },
    staticEdge          { m_container,         WS_EX_STATICEDGE,       L"WS_EX_STATICEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::staticEdge         },
    toolWindow          { m_container,         WS_EX_TOOLWINDOW,       L"WS_EX_TOOLWINDOW", x, height * row++, width, height ,Window::ExtendedStyles::Description::toolWindow         },
    topMost             { m_container,            WS_EX_TOPMOST,          L"WS_EX_TOPMOST", x, height * row++, width, height ,Window::ExtendedStyles::Description::topMost            },
    transparent         { m_container,        WS_EX_TRANSPARENT,      L"WS_EX_TRANSPARENT", x, height * row++, width, height ,Window::ExtendedStyles::Description::transparent        },
    windowEdge          { m_container,         WS_EX_WINDOWEDGE,       L"WS_EX_WINDOWEDGE", x, height * row++, width, height ,Window::ExtendedStyles::Description::windowEdge         },

    dwmAttributes{ m_container, L"DWM Attributes", (x = 1500), (row = 1, 0), 500, 1000},
    ncRendering{ m_container, L"DWM NCRendering", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_NCRENDERING_POLICY, DWMNCRENDERINGPOLICY::DWMNCRP_ENABLED, DWMNCRENDERINGPOLICY::DWMNCRP_DISABLED },
    transition{ m_container, L"Transition", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_TRANSITIONS_FORCEDISABLED, FALSE, TRUE },
    allowNCPaint{ m_container, L"Allow NC paint", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_ALLOW_NCPAINT, TRUE, FALSE },
    ncRightToLeftLayout{ m_container, L"NC Right to Left layout", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_NONCLIENT_RTL_LAYOUT, TRUE, FALSE },
    forceIconicPresentation{ m_container, L"Force iconic representation", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_FORCE_ICONIC_REPRESENTATION, TRUE, FALSE },
    hasIconicBitmap{ m_container, L"Has iconic bitmap", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_HAS_ICONIC_BITMAP, TRUE, FALSE },
    flip3D
    {
        {
            DwmAttributeRadioButton{m_container, L"DWMFLIP3D_DEFAULT",        x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_DEFAULT},
            DwmAttributeRadioButton{m_container, L"DWMFLIP3D_EXCLUDEBELOW",   x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_EXCLUDEBELOW},
            DwmAttributeRadioButton{m_container, L"DWMFLIP3D_EXCLUDEABOVE",   x + 50, height * row++, width, height, DWMWA_FLIP3D_POLICY, DWMFLIP3DWINDOWPOLICY::DWMFLIP3D_EXCLUDEABOVE},
        }
    },
    disallowPeek{ m_container, L"Disallow peek", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_DISALLOW_PEEK, TRUE, FALSE },
    excludedFromPeek{ m_container, L"Excluded from peek", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_EXCLUDED_FROM_PEEK, TRUE, FALSE },
    dwmCloak{ m_container, L"DWM Cloak", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_CLOAK, TRUE, FALSE },
    freezeRepresentation{ m_container, L"Freeze representation", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_FREEZE_REPRESENTATION, TRUE, FALSE },
    
    //Windows 11 attributes
   useHostBackdropBrush   {m_container, L"Use host backdrop brush", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_USE_HOSTBACKDROPBRUSH, TRUE, FALSE},
   useImmersiveDarkMode   {m_container, L"Use immersive dark mode", x, height * row++, width, height, DWMWINDOWATTRIBUTE::DWMWA_USE_IMMERSIVE_DARK_MODE, TRUE, FALSE},
   windowCornerPreference
   {
       {
            DwmAttributeRadioButton{m_container, L"DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DEFAULT},
            DwmAttributeRadioButton{m_container, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_DONOTROUND", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_DONOTROUND},
            DwmAttributeRadioButton{m_container, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_ROUND", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUND},
            DwmAttributeRadioButton{m_container, L"DWM_WINDOW_CORNER_PREFERENCE::DWM_ROUNDSMALL", x, height * row++, width, height, DWMWA_WINDOW_CORNER_PREFERENCE, DWM_WINDOW_CORNER_PREFERENCE::DWMWCP_ROUNDSMALL},
       }
   },
   borderColor            {m_container, L"Border color", x, height * row++, width, height},
   captionColor           {m_container, L"Caption color", x, height * row++, width, height},
    createButton{ m_container, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 600, width, height },
    assist{ m_container, L"Window style assist", 1000, 700, width, height },
    closeButton{ m_container, static_cast<DWORD>(Controls::Button::Style::PushButton), 1000, 850, width, height }
{
    layered.onClick([this](HWND)
    {
    	//make RGB and transparency slider
        LayeredWindowAttributes::GetInstance(m_container).setVisible(layered.isChecked());
    });

   createButton.setText(L"Create window");
   createButton.onClick([&](HWND)
   {
   	//Create window


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

   	
   	    gCreatedWindow.create(extendedStyle, style, os);
   

       //SetWindowLongPtr(gCreatedWindow, GWL_STYLE, style);
       //SetWindowLongPtr(gCreatedWindow, GWL_EXSTYLE, extendedStyle);
       gCreatedWindow.setStyle(style);
       gCreatedWindow.setExtendedStyle(extendedStyle);

       if (layered.isChecked())
           LayeredWindowAttributes::MakeLayeredWindow(m_container);

       if (gCreatedWindow)
           gCreatedWindow.show(UI::Window::ShowType::Show);
       gCreatedWindow.update();
       OutputDebugString(L"Create window");
   });

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

   closeButton.setText(L"Close window");
   closeButton.onClick([](HWND)
   {
       if (gCreatedWindow)
       {
           DestroyWindow(gCreatedWindow);
           OutputDebugString(L"Close window");
       }
   });

   for (int i = 0; i < 3; ++i)
   {
       flip3D[i].addHandler();
   }
   flip3D.addHandler();

   for (int i = 0; i < 4; ++i)
   {
       windowCornerPreference[i].addHandler();
    }
   windowCornerPreference.addHandler();
}

void Gallery::Pages::WindowPage::Page::hide()
{
    if (m_container)
        ShowWindow(m_container, SW_HIDE);
}

void Gallery::Pages::WindowPage::Page::show()
{
    if (m_container)
        ShowWindow(m_container, SW_SHOW);
}

#pragma once

#include "resource.h"

#include "Gallery.TabPageBase.h"
#include "Gallery.Pages.WindowPage.WindowStyleCheckbox.h"
#include "Gallery.Slider.h"
#include "Gallery.Pages.WindowPage.DwmAttributeCheckbox.h"
#include "Gallery.Pages.WindowPage.DwmAttributeRadioButton.h"
#include "Gallery.Pages.WindowPage.ExampleWindow.h"
#include "Gallery.RadioButtonGroup.h"
#include "Gallery.Pages.WindowPage.WindowStyleAssist.h"

void InitWindow();
void Init();

namespace Gallery::Pages::WindowPage
{
	class Page : public TabPageBase
	{
		Groupbox windowStyles;
		WindowStyleCheckbox border;
		WindowStyleCheckbox caption;
		WindowStyleCheckbox child;
		WindowStyleCheckbox childWindow;
		WindowStyleCheckbox clipSiblings;
		WindowStyleCheckbox clipChildren;
		WindowStyleCheckbox disabled;
		WindowStyleCheckbox dlgFrame;
		WindowStyleCheckbox group           ;
		WindowStyleCheckbox hScroll         ;
		WindowStyleCheckbox vScroll         ;
	    WindowStyleCheckbox iconic          ;
		WindowStyleCheckbox minimize        ;
		WindowStyleCheckbox maximize        ;
		WindowStyleCheckbox maximizeBox     ;
		WindowStyleCheckbox minimizeBox     ;
		WindowStyleCheckbox overlapped      ;
		WindowStyleCheckbox overlappedWindow;
		WindowStyleCheckbox popUp           ;
		WindowStyleCheckbox popUpWindow     ;
		WindowStyleCheckbox sizeBox         ;
		WindowStyleCheckbox sysMenu         ;
		WindowStyleCheckbox tabStop         ;
		WindowStyleCheckbox thickFrame      ;
	    WindowStyleCheckbox tiled           ;
		WindowStyleCheckbox tiledWindow     ;
		WindowStyleCheckbox visible         ;
		
		Groupbox extendedStyles;
		WindowStyleCheckbox acceptFiles         ;
		WindowStyleCheckbox appWindow           ;
		WindowStyleCheckbox clientEdge          ;
		WindowStyleCheckbox composited          ;
		WindowStyleCheckbox contextHelp         ;
		WindowStyleCheckbox controlParent       ;
		WindowStyleCheckbox dlgModalFrame       ;
		WindowStyleCheckbox layered             ;
		WindowStyleCheckbox layoutRTL           ;
		WindowStyleCheckbox left                ;
		WindowStyleCheckbox leftScrollBar       ;
		WindowStyleCheckbox leftToRight         ;
		WindowStyleCheckbox mdiChild            ;
		WindowStyleCheckbox noActivate          ;
		WindowStyleCheckbox noInheritLayout     ;
		WindowStyleCheckbox noParentNotify      ;
		WindowStyleCheckbox noRedirectionBitmap ;
		WindowStyleCheckbox exOverlappedWindow  ;
		WindowStyleCheckbox paletteWindow       ;
		WindowStyleCheckbox right               ;
		WindowStyleCheckbox rightScrollBar      ;
		WindowStyleCheckbox rightToLeft         ;
		WindowStyleCheckbox staticEdge          ;
		WindowStyleCheckbox toolWindow          ;
		WindowStyleCheckbox topMost             ;
		WindowStyleCheckbox transparent         ;
		WindowStyleCheckbox windowEdge          ;

		Groupbox dwmAttributes;
		DwmAttributeCheckbox<decltype(DWMNCRP_ENABLED)> ncRendering;
		DwmAttributeCheckbox<decltype(TRUE)> transition             ;
		DwmAttributeCheckbox<decltype(TRUE)> allowNCPaint           ;
		DwmAttributeCheckbox<decltype(TRUE)> ncRightToLeftLayout    ;
		DwmAttributeCheckbox<decltype(TRUE)> forceIconicPresentation;
		DwmAttributeCheckbox<decltype(TRUE)> hasIconicBitmap        ;
		RadioButtonGroup<DwmAttributeRadioButton<decltype(DWMFLIP3D_DEFAULT)>> flip3D;
		DwmAttributeCheckbox<decltype(TRUE)> disallowPeek           ;
		DwmAttributeCheckbox<decltype(TRUE)> excludedFromPeek       ;
		DwmAttributeCheckbox<decltype(TRUE)> dwmCloak               ;
		DwmAttributeCheckbox<decltype(TRUE)> freezeRepresentation   ;
	    //Windows 11 attributes
	    DwmAttributeCheckbox<decltype(TRUE)> useHostBackdropBrush   ;
	    DwmAttributeCheckbox<decltype(TRUE)> useImmersiveDarkMode   ;
		RadioButtonGroup<DwmAttributeRadioButton<decltype(DWMWCP_DEFAULT)>> windowCornerPreference;
		Checkbox borderColor            ;
		Checkbox captionColor           ;

		ButtonEx createButton;
		Checkbox assist;
		ButtonEx closeButton;
	public:
		Page(HWND hwnd, int width = 200, int height = 50, int row = 1, int x = 20);
		void hide() override;
		void show() override;
	};
}
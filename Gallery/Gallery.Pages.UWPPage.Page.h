#pragma once
#include "Gallery.TabPageBase.h"
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.system.h>
#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/UWPCppProj.h>

namespace Gallery::Pages::UWPPage
{
	class Page : public TabPageBase
	{
		winrt::UWPCppProj::App m_hostApp{ nullptr };
		winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource m_desktopWindowXamlSource{ nullptr };
		winrt::UWPCppProj::MyUserControl m_myControl{ nullptr };
	public:
		Page(HWND container);
	};
}
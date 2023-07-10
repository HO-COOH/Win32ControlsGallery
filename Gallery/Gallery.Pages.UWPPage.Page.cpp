#include "pch.h"
#include "Gallery.Pages.UWPPage.Page.h"

namespace Gallery::Pages::UWPPage
{
	Page::Page(HWND container) : TabPageBase{ container, L"UWP Interop" }
	{
		m_hostApp = winrt::UWPCppProj::App();
		m_desktopWindowXamlSource = winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource{};

		auto interop = m_desktopWindowXamlSource.as<IDesktopWindowXamlSourceNative>();
		winrt::check_hresult(interop->AttachToWindow(m_container));
		HWND hWndXamlIsland = nullptr;
		interop->get_WindowHandle(&hWndXamlIsland);
		RECT windowRect;
		GetWindowRect(m_container, &windowRect);
		SetWindowPos(hWndXamlIsland, NULL, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, SWP_SHOWWINDOW);

		m_myControl = winrt::UWPCppProj::MyUserControl();
		m_desktopWindowXamlSource.Content(m_myControl);


	}
}
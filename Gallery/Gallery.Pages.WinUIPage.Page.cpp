#include "pch.h"
#include "Gallery.Pages.WinUIPage.Page.h"
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.system.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <future>

using namespace winrt;
using namespace winrt::Windows;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml::Hosting;

extern HWND gHwnd;

namespace Gallery::Pages::WinUIPage
{

    winrt::Windows::Foundation::IAsyncAction Page::ShowDialog(winrt::Windows::UI::Xaml::XamlRoot const& xamlRoot)
    {
        winrt::Windows::UI::Xaml::Controls::ContentDialog dialog;
        dialog.Title(winrt::box_value(L"WinUI Dialog Title"));
        dialog.PrimaryButtonText(L"Primary Button");
        dialog.SecondaryButtonText(L"Secondary Button");
        dialog.CloseButtonText(L"Close Button");
        dialog.Content(winrt::box_value(L"This is a WinUI dialog"));
        dialog.XamlRoot(xamlRoot);
        co_await dialog.ShowAsync();
    }

	Page::Page(HWND container) : TabPageBase{container, L"WinUI Interop"}
	{
        auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
        interop->AttachToWindow(m_container);
        HWND hWndXamlIsland{};
        interop->get_WindowHandle(&hWndXamlIsland);

		RECT rect{};
		GetClientRect(m_container, &rect);
        SetWindowPos(hWndXamlIsland, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
        // Create the XAML content.
        Windows::UI::Xaml::Controls::StackPanel xamlContainer;
        //xamlContainer.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::LightGray() });
        Windows::UI::Xaml::Controls::Button b;
        b.Content(winrt::box_value(L"Click me!"));
        b.Click([](winrt::Windows::Foundation::IInspectable sender, auto) -> winrt::Windows::Foundation::IAsyncAction {
            auto parent = sender.as<winrt::Windows::UI::Xaml::FrameworkElement>().Parent();
            co_await ShowDialog(parent.as<winrt::Windows::UI::Xaml::UIElement>().XamlRoot());
        });


        xamlContainer.Children().Append(b);
        xamlContainer.UpdateLayout();
        desktopSource.Content(xamlContainer);
	}
}

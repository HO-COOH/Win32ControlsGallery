#pragma once


#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.system.h>
#include <winrt/windows.ui.xaml.hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/Windows.ui.xaml.media.h>


using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;

inline void Init()
{

    //init winrt
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    auto windowsXamlManager = WindowsXamlManager::InitializeForCurrentThread();
    DesktopWindowXamlSource desktopSource;
    auto interop = desktopSource.as<IDesktopWindowXamlSourceNative>();
    interop->AttachToWindow(gHwnd);
    HWND hWndXamlIsland{};
    interop->get_WindowHandle(&hWndXamlIsland);
    SetWindowPos(hWndXamlIsland, 0, 500, 100, 800, 200, SWP_SHOWWINDOW);
    // Create the XAML content.
    Windows::UI::Xaml::Controls::StackPanel xamlContainer;
    xamlContainer.Background(Windows::UI::Xaml::Media::SolidColorBrush{ Windows::UI::Colors::LightGray() });

    //Windows::UI::Xaml::Controls::TextBlock tb;
    //tb.Text(L"Hello World from Xaml Islands!");
    //tb.VerticalAlignment(Windows::UI::Xaml::VerticalAlignment::Center);
    //tb.HorizontalAlignment(Windows::UI::Xaml::HorizontalAlignment::Center);
    //tb.FontSize(48);
    Windows::UI::Xaml::Controls::Button b;
    b.Content(winrt::box_value(L"Click me!"));


    xamlContainer.Children().Append(b);
    xamlContainer.UpdateLayout();
    desktopSource.Content(xamlContainer);
}
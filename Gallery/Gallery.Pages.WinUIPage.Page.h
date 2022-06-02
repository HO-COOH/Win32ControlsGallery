#pragma once

#include "Gallery.TabPageBase.h"
#include <winrt/windows.ui.xaml.hosting.h>

namespace Gallery::Pages::WinUIPage
{
    class Page : public TabPageBase
    {
        static inline winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager windowsXamlManager{ nullptr };
        winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;
        static winrt::Windows::Foundation::IAsyncAction ShowDialog(winrt::Windows::UI::Xaml::XamlRoot const& xamlRoot);
    public:
        static void Init();
        Page(HWND container);
    };

}

#include "pch.h"

#include "App.h"
#include "App.g.cpp"
/// <summary>
/// Creates the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
namespace winrt::UWPCppProj::implementation
{
    App::App()
    {
        Initialize();
        AddRef();
        m_inner.as<::IUnknown>()->Release();
    }
    App::~App()
    {
        Close();
    }
}
# Win32 Controls Gallery
[Microsoft Doc](https://docs.microsoft.com/en-us/windows/win32/controls/individual-control-info)
[AvaloniaUI Xaml Controls Gallery](https://github.com/AvaloniaUI/XamlControlsGallery)
[WinUI Gallery](https://github.com/microsoft/WinUI-Gallery)

## Build
### Linking
Link with `User32.dll` and `Comctl32.dll`

## Notes
- Member functions are provided by macros, that are internally a window message send to a control and returned a result
- **Textblock** (that simply displays text) is called **Static control**
- [High DPI changes example](https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/DPIAwarenessPerWindow/client/DpiAwarenessContext.cpp)
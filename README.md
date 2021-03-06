# Win32 Controls Gallery

For more "galleries", visit:
- [Microsoft Doc](https://docs.microsoft.com/en-us/windows/win32/controls/individual-control-info)
- [AvaloniaUI Xaml Controls Gallery](https://github.com/AvaloniaUI/XamlControlsGallery)
- [WinUI Gallery](https://github.com/microsoft/WinUI-Gallery)

## Usage
The library is written in layers.

### Core
Core layer is a thin, object-oriented, *header-only* wrapper around the [Common Win32 controls](https://docs.microsoft.com/en-us/windows/win32/controls/window-controls).
The controls are objects under `namespace Controls`. 
Current controls:
|Controls|Objects|
|---|---|
|[Tab](https://docs.microsoft.com/en-us/windows/win32/controls/tab-control-reference) |`Controls::Tab`
|[Button](https://docs.microsoft.com/en-us/windows/win32/controls/buttons) |`Controls::Button`
|[Progrss Bar](https://docs.microsoft.com/en-us/windows/win32/controls/progress-bar-control-reference) |`Controls::ProgresBar`
|[UpDown](https://docs.microsoft.com/en-us/windows/win32/controls/up-down-controls)|`Controls::UpDown`
|[Static](https://docs.microsoft.com/en-us/windows/win32/controls/static-controls)|`Controls::Static`
|[Edit Control](https://docs.microsoft.com/en-us/windows/win32/controls/edit-controls)|`Controls::TextEdit`
|[Trackbar](https://docs.microsoft.com/en-us/windows/win32/controls/trackbar-control-reference)|`Controls::Trackbar`
|[Tooltip](https://docs.microsoft.com/en-us/windows/win32/controls/tooltip-control-reference)|`Controls::Tooltip`

Also thin wrapper around common Win32 APIs
- `namespace UI`
    + `namespace UI::Dwm`: Dwm APIs controlling window composition
    + `namespace UI::Window`: Win32 Windowing APIs
    + `namespace UI::Shell`: Win32 Shell integration APIs (such as taskbar icons, notifications, etc.)
- `namespace Util`
    + `namespace Util::Error`
    + `namespace Util::System`

#### Porting from old code
| Old code | New code| Example
|---|---|---|
|Create controls using `CreateWindowEx()`|Construct control objects| `Controls::Button button{parent, Controls::Button::Style::PushButton}`
|Modify control states with window messages `SendMessage()`|Call member functions|`button.setText(L"MyButton")`
|Use pre-defined macros| Use class-scoped enums | `Button::Style::PushButton`
|Composing bit flags with bitwise or  | Composing bit flags with variadic templates | 
|Pass parameters as pointers to window messages | Pass parameters as references to member functions | `SIZE size{}; button.getIdealSize(size);`

#### Porting from MFC
|MFC code | New code | Example
|---|---|---|
|Create controls with `.Create()` virtual function | Create controls with constructors (also optionally with `.create()` ) | `Controls::Button button{parent};`
|`PascalCase` for member functions | `camelCase` for member functions | `button.setText(L"MyButton");`
|Use pre-defined macros | Use class-scoped enums | `Button::Style::PushButton`



### Framework
Built on top of the core layer, the framework layers provides a higher-level, declarative construct for building UI.


## Examples
- Window gallery: All window styles with interactive switches that applies to an example window in real time, including:
  + `WS_` window styles
  + `WS_EX_` extended window styles
  + DWM attributes
  + custom rendering
![](assets/Window.png)
- WinUI Interop: Hosting WinUI Xaml controls
![](assets/WinUIInterop.png)

## Build
C++20 is used. Use Visual Studio 2022 to build the solution.

## Notes
- Member functions are provided by macros, that are internally a window message send to a control and returned a result
- **Textblock** (that simply displays text) is called **Static control**
- When creating a `TOOLINFO` struct, remember to set `.cbSize` member to `sizeof(TOOLINFO) - sizeof(void*)`, the
  reason being
```cpp
/*CommCtrl.h Line: 2256*/
typedef struct tagTOOLINFOW {
    UINT cbSize;
    UINT uFlags;
    HWND hwnd;
    UINT_PTR uId;
    RECT rect;
    HINSTANCE hinst;
    LPWSTR lpszText;
    LPARAM lParam;
#if (NTDDI_VERSION >= NTDDI_WINXP)
    void *lpReserved;
#endif
} TTTOOLINFOW, NEAR *PTOOLINFOW, *LPTTTOOLINFOW;
```
- Layered window does not show until a `SetLayeredWindowAttributes()` is called. 
  This function actually works in this way:
    + If `LWA_COLORKEY` is used, the color of the color argument becomes transparent.
	  By default the window is white, so the white is "removed"
	+ If `LWA_ALPHA` is used, the alpha value of the color argument is used, the whole window gets partially transparent.
	If the window is completely transparent, which means it meets one of the following conditions:
	+ The whole window has the same color as the color argument and `LWA_COLORKEY` is used
	+ The alpha arguments is `0` and `LWA_ALPHA` is used.
	The window becomes `transparent`, that does not captures mouse inputs, including the title bar (if exists)
- [High DPI changes example](https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/DPIAwarenessPerWindow/client/DpiAwarenessContext.cpp)
- If you don't fill the `.hWnd` member in `NOTIFYICONDATA` struct, calling `Shell_NotifyIcon()` will cause a sort of one-time notification effect.
 Where the icon and notification still shows, but will disappear as soon as your mouse cursor hover over it.

 - The `UpDown Control` by default sets the minimum to 100 and maximum to 0. (You can use an `Edit Control` as its buddy window to confirm that).
As a result, pressing the up arrow decrease the value and the down arrow increase the value, which is probably not what you intended.
To flip that, use `setRange()` function to swap the maximum and minimum value.
- To use Xaml Island with system Xaml, install `Microsoft.Toolkit.Win32.UI.SDK` nuget package
- To use Windows App SDK, follow [this guide](https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/use-windows-app-sdk-in-existing-project)
- [Multi-color text formatting](https://www.codeproject.com/Articles/12093/Using-RichEditCtrl-to-Display-Formatted-Logs)
- mfc wrapper of gdi object is in header `<afxwin.h>`, and you need to include it before `#include <windows.h>`
- [win32 custom title bar explained](https://kubyshkin.name/posts/win32-window-custom-title-bar-caption/)
- [Flicker-Free Displays Using an Off-Screen DC](https://docs.microsoft.com/en-us/previous-versions/ms969905(v=msdn.10)?redirectedfrom=MSDN)
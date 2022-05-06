#pragma once

namespace Window::Styles::Description
{
	//https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
	
	constexpr auto border = L"The window has a thin-line border.";
	
	constexpr auto caption = L"The window has a title bar (includes the WS_BORDER style).";

	constexpr auto child = L"The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the WS_POPUP style.";

	constexpr auto childWindow = L"Same as the WS_CHILD style.";

	constexpr auto clipChildren = L"Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.";
	
	constexpr auto clipSiblings = L"Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.";
	
	constexpr auto disabled = L"The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.";
	
	constexpr auto dlgFrame = L"The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.";

	constexpr auto group = L"The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. The first control in each group usually has the WS_TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys. You can turn this style on and off to change dialog box navigation.To change this style after a window has been created, use the SetWindowLong function.";

	constexpr auto hScroll = L"The window has a horizontal scroll bar.";
	
	constexpr auto iconic = L"The window is initially minimized. Same as the WS_MINIMIZE style.";
	
	constexpr auto maximize = L"The window is initially maximized.";

	constexpr auto maximizeBox = L"The window has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.";
	
	constexpr auto minimize = L"The window is initially minimized. Same as the WS_ICONIC style.";
	
	constexpr auto minimizeBox = L"The window has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.";

	constexpr auto overlapped = L"The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_TILED style.";

	constexpr auto overlappedWindow = L"The window is an overlapped window. Same as the WS_TILEDWINDOW style.";

	constexpr auto popUp = L"The window is a pop-up window. This style cannot be used with the WS_CHILD style.";

	constexpr auto popUpWindow = L"The window is a pop-up window. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible.";

	constexpr auto sizeBox = L"The window has a sizing border. Same as the WS_THICKFRAME style.";

	constexpr auto sysMenu = L"The window has a window menu on its title bar. The WS_CAPTION style must also be specified.";

	constexpr auto tabStop = L"The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style. You can turn this style on and off to change dialog box navigation.To change this style after a window has been created, use the SetWindowLong function.For user - created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.";

	constexpr auto thickFrame = L"The window has a sizing border. Same as the WS_SIZEBOX style.";

	constexpr auto tiled = L"The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_OVERLAPPED style.";

	constexpr auto tiledWindow = L"The window is an overlapped window. Same as the WS_OVERLAPPEDWINDOW style.";

	constexpr auto visible = L"The window is initially visible. This style can be turned on and off by using the ShowWindow or SetWindowPos function.";

	constexpr auto vScroll = L"The window has a vertical scroll bar.";
}

namespace Window::ExtendedStyles::Description
{
	constexpr auto acceptFiles = L"The window accepts drag-drop files.";

	constexpr auto appWindow = L"Forces a top-level window onto the taskbar when the window is visible.";

	constexpr auto clientEdge = L"The window has a border with a sunken edge.";

	constexpr auto composited = L"Paints all descendants of a window in bottom-to-top painting order using double-buffering. Bottom-to-top painting order allows a descendent window to have translucency (alpha) and transparency (color-key) effects, but only if the descendent window also has the WS_EX_TRANSPARENT bit set. Double-buffering allows the window and its descendents to be painted without flicker. This cannot be used if the window has a class style of either CS_OWNDC or CS_CLASSDC. Windows 2000: This style is not supported.";

	constexpr auto contextHelp = L"The title bar of the window includes a question mark. When the user clicks the question mark, the cursor changes to a question mark with a pointer. If the user then clicks a child window, the child receives a WM_HELP message. The child window should pass the message to the parent window procedure, which should call the WinHelp function using the HELP_WM_HELP command. The Help application displays a pop-up window that typically contains help for the child window. WS_EX_CONTEXTHELP cannot be used with the WS_MAXIMIZEBOX or WS_MINIMIZEBOX styles.";

	constexpr auto controlParent = L"The window itself contains child windows that should take part in dialog box navigation. If this style is specified, the dialog manager recurses into children of this window when performing navigation operations such as handling the TAB key, an arrow key, or a keyboard mnemonic.";

	constexpr auto dlgModalFrame = L"The window has a double border; the window can, optionally, be created with a title bar by specifying the WS_CAPTION style in the dwStyle parameter.";

	constexpr auto layered = L"The window is a layered window. This style cannot be used if the window has a class style of either CS_OWNDC or CS_CLASSDC. Windows 8: The WS_EX_LAYERED style is supported for top - level windows and child windows.Previous Windows versions support WS_EX_LAYERED only for top - level windows.";

	constexpr auto layoutRTL = L"If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the horizontal origin of the window is on the right edge. Increasing horizontal values advance to the left.";

	constexpr auto left = L"The window has generic left-aligned properties. This is the default.";

	constexpr auto leftScrollBar = L"If the shell language is Hebrew, Arabic, or another language that supports reading order alignment, the vertical scroll bar (if present) is to the left of the client area. For other languages, the style is ignored.";

	constexpr auto leftToRight = L"The window text is displayed using left-to-right reading-order properties. This is the default.";
	
	constexpr auto mdiChild = L"The window is a MDI child window.";

	constexpr auto noActivate = L"A top-level window created with this style does not become the foreground window when the user clicks it. The system does not bring this window to the foreground when the user minimizes or closes the foreground window.The window should not be activated through programmatic access or via keyboard navigation by accessible technology, such as Narrator. To activate the window, use the SetActiveWindow or SetForegroundWindow function. The window does not appear on the taskbar by default.To force the window to appear on the taskbar, use the WS_EX_APPWINDOW style.";
	
	constexpr auto noInheritLayout = L"The window does not pass its window layout to its child windows.";
	
	constexpr auto noParentNotify = L"The child window created with this style does not send the WM_PARENTNOTIFY message to its parent window when it is created or destroyed.";

	constexpr auto noRedirectionBitmap = L"The window does not render to a redirection surface. This is for windows that do not have visible content or that use mechanisms other than surfaces to provide their visual.";

	constexpr auto overlappedWindow = L"The window is an overlapped window.";

	constexpr auto paletteWindow = L"The window is palette window, which is a modeless dialog box that presents an array of commands.";

	constexpr auto right = L"The window has generic \"right - aligned\" properties. This depends on the window class. This style has an effect only if the shell language is Hebrew, Arabic, or another language that supports reading-order alignment; otherwise, the style is ignored. Using the WS_EX_RIGHT style for static or edit controls has the same effect as using the SS_RIGHT or ES_RIGHT style, respectively.Using this style with button controls has the same effect as using BS_RIGHTand BS_RIGHTBUTTON styles.";

	constexpr auto rightScrollBar = L"The vertical scroll bar (if present) is to the right of the client area. This is the default.";
	
	constexpr auto rightToLeft = L"If the shell language is Hebrew, Arabic, or another language that supports reading-order alignment, the window text is displayed using right-to-left reading-order properties. For other languages, the style is ignored.";
	
	constexpr auto staticEdge = L"The window has a three-dimensional border style intended to be used for items that do not accept user input.";

	constexpr auto toolWindow = L"The window is intended to be used as a floating toolbar. A tool window has a title bar that is shorter than a normal title bar, and the window title is drawn using a smaller font. A tool window does not appear in the taskbar or in the dialog that appears when the user presses ALT+TAB. If a tool window has a system menu, its icon is not displayed on the title bar. However, you can display the system menu by right-clicking or by typing ALT+SPACE.";

	constexpr auto topMost = L"The window should be placed above all non-topmost windows and should stay above them, even when the window is deactivated. To add or remove this style, use the SetWindowPos function.";

	constexpr auto transparent = L"The window should not be painted until siblings beneath the window (that were created by the same thread) have been painted. The window appears transparent because the bits of underlying sibling windows have already been painted. To achieve transparency without these restrictions, use the SetWindowRgn function.";
	
	constexpr auto windowEdge = L"The window has a border with a raised edge.";
}
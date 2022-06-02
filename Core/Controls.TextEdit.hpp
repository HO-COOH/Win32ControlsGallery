#pragma once
#include "Controls.Control.hpp"
#include <windowsx.h>
#include <vector>

namespace Controls
{
	class TextEdit : public Control
	{
		//Constants
		constexpr static auto ClassName = L"EDIT";
	public:
		enum class Styles
		{
			AutoHScroll = ES_AUTOHSCROLL,
			AutoVScroll = ES_AUTOVSCROLL,
			Center = ES_CENTER,
			Left = ES_LEFT,
			LowerCase = ES_LOWERCASE,
			MultiLine = ES_MULTILINE,
			NoHideSel = ES_NOHIDESEL,
			Number = ES_NUMBER,
			OemConvert = ES_OEMCONVERT,
			Password = ES_PASSWORD,
			ReadOnly = ES_READONLY,
			Right = ES_RIGHT,
			UpperCase = ES_UPPERCASE,
			WantReturn = ES_WANTRETURN
		};

		TextEdit(HWND parent, DWORD styles, int x, int y, int width, int height)
		{
			m_hwnd = CreateWindowEx(0, ClassName, NULL, styles | WS_CHILD | WS_VISIBLE,
				x, y, width, height, parent, NULL, NULL, NULL);

		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_canundo
		//return value is not void
		bool canUndo() const
		{
			return Edit_CanUndo(m_hwnd);
		}

		void emptyUndoBuffer()
		{
			Edit_EmptyUndoBuffer(m_hwnd);
		}

		void enable(bool enable = true)
		{
			Edit_Enable(m_hwnd, enable);
		}

		void disable()
		{
			Edit_Enable(m_hwnd, false);
		}

		void fmtLines(bool addEOL)
		{
			Edit_FmtLines(m_hwnd, addEOL);
		}

		auto getFirstVisibleLine() const
		{
			return Edit_GetFirstVisibleLine(m_hwnd);
		}

		//renamed from Edit_GetHandle
		auto getBuffer() const
		{
			return static_cast<HLOCAL>(Edit_GetHandle(m_hwnd));
		}

		auto getLine(int lineIndex, LPTSTR buffer, int maxNumChars) const
		{
			return Edit_GetLine(m_hwnd, lineIndex, buffer, maxNumChars);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_getlinecount
		//wrong return value
		auto getLineCount() const
		{
			return Edit_GetLineCount(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_getmodify
		//wrong return value
		auto isModified() const
		{
			return Edit_GetModify(m_hwnd);
		}

		auto getPasswordChar() const
		{
			return Edit_GetPasswordChar(m_hwnd);
		}

		auto getRect() const
		{
			RECT rect{};
			Edit_GetRect(m_hwnd, &rect);
			return rect;
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_getsel
		//wrong return value
		auto getSel()
		{
			Range<DWORD> range{};
			sendMessage(EM_GETSEL, reinterpret_cast<WPARAM>(&range.min), reinterpret_cast<WPARAM>(&range.max));
			return range;
		}

		auto getText(LPTSTR buffer, int numMaxChars) const
		{
			return Edit_GetText(m_hwnd, buffer, numMaxChars);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_gettextlength
		//wrong return value
		auto getTextLength() const
		{
			return Edit_GetTextLength(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_getwordbreakproc
		//wrong return value
		auto getWordBreakProc() const
		{
			return Edit_GetWordBreakProc(m_hwnd);
		}

		void limitText(int numMaxChars)
		{
			Edit_LimitText(m_hwnd, numMaxChars);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_linefromchar
		//wrong return value
		auto lineFromChar(int charIndex) const
		{
			return Edit_LineFromChar(m_hwnd, charIndex);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_lineindex
		//wrong return value
		auto lineIndex(int lineIndex) const
		{
			return Edit_LineIndex(m_hwnd, lineIndex);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/windowsx/nf-windowsx-edit_linelength
		//wrong return value
		auto lineLength(int lineIndex) const
		{
			return Edit_LineLength(m_hwnd, lineIndex);
		}

		void replaceSel(LPCTSTR text)
		{
			Edit_ReplaceSel(m_hwnd, text);
		}

		void scroll(int verticalAmount, int horizontalAmount)
		{
			Edit_Scroll(m_hwnd, verticalAmount, horizontalAmount);
		}

		void scrollCaret()
		{
			Edit_ScrollCaret(m_hwnd);
		}

		void setBuffer(HLOCAL handle)
		{
			Edit_SetHandle(m_hwnd, handle);
		}

		void setModify(bool modify)
		{
			Edit_SetModify(m_hwnd, modify);
		}

		void setPasswordChar(UINT character)
		{
			Edit_SetPasswordChar(m_hwnd, character);
		}

		void setReadOnly(bool readOnly)
		{
			Edit_SetReadOnly(m_hwnd, readOnly);
		}

		void setRect(RECT const* rect)
		{
			Edit_SetRect(m_hwnd, rect);
		}

		void setRectNoPaint(RECT const* rect)
		{
			Edit_SetRectNoPaint(m_hwnd, rect);
		}

		void setSel(Range<int> range)
		{
			Edit_SetSel(m_hwnd, range.min, range.max);
		}

		void setTabStops(std::vector<int> const& tabStops)
		{
			Edit_SetTabStops(m_hwnd, tabStops.size(), tabStops.data());
		}

		void setText(LPCTSTR text)
		{
			Edit_SetText(m_hwnd, text);
		}

		void setWordBreakProc(EDITWORDBREAKPROC func)
		{
			Edit_SetWordBreakProc(m_hwnd, func);
		}
	};
}
#pragma once

#include "resource.h"

namespace Controls
{
	void InitWindow();
	void InitControls();
	void Init();
	
	DWORD StringLength(LPCSTR str);
	DWORD StringLength(LPCWSTR str);
	
	RECT GetClientRect(HWND hwnd);

	class Tab
	{
		HWND m_hwnd;

	public:
		Tab(HWND parent);

		void addTab(TCITEM const& item);
		void addTab(LPCTSTR text);

		//methods
		void adjustRect(BOOL larger, RECT& rect);
		void deleteAllItems();
		void deleteItem(int i);
		void deselectAll(UINT excludeFocus);
		int getCurFocus();
		int getCurSel() const; //wrong doc
		DWORD getExtendedStyle();
		HIMAGELIST getImageList();
		TCITEM getItem(int iItem, UINT mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT);
		int getItemCount();
		RECT getItemRect(int i);
		int getRowCount();
		HWND getToolTips();
		BOOL getUnicodeFormat();
		void highlightItem(int i, WORD highlight);
		int hitTest(TCHITTESTINFO const& info);
		void removeImage(int i);
		void setCurFocus(int i);
		void setExtendedStyle(DWORD styles);
		void setImageList(HIMAGELIST list);
		void setItem(int i, TCITEM const& item);
		void setItemExtra(int extraBytes);
		void setItemSize(int x, int y);
		void setMinTabWidth(int x);
		void setPadding(int cx, int cy);
		void setToolTips(HWND tooltip);
		void setUnicodeFormat(BOOL unicode);
		
		//Constants
		constexpr static auto ClassName = WC_TABCONTROL;
	};
}
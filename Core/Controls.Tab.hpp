#pragma once
#include "Controls.Control.hpp"
#include <WinUser.h>
#include <CommCtrl.h>

namespace Controls
{
	class Tab : public Control
	{

	public:
		inline Tab(HWND parent);

		inline void addTab(int index, TCITEM const& item);
		inline void addTab(int index, LPCTSTR text);

		//methods
		inline void adjustRect(BOOL larger, RECT& rect);
		inline void deleteAllItems();
		inline void deleteItem(int i);
		inline void deselectAll(UINT excludeFocus);
		inline int getCurFocus();
		inline int getCurSel() const; //wrong doc
		inline DWORD getExtendedStyle();
		inline HIMAGELIST getImageList();
		inline TCITEM getItem(int iItem, UINT mask = TCIF_IMAGE | TCIF_PARAM | TCIF_STATE | TCIF_TEXT);
		inline int getItemCount();
		inline RECT getItemRect(int i);
		inline int getRowCount();
		inline HWND getToolTips();
		inline BOOL getUnicodeFormat();
		inline void highlightItem(int i, WORD highlight);
		inline int hitTest(TCHITTESTINFO const& info);
		inline void removeImage(int i);
		inline void setCurFocus(int i);
		inline void setExtendedStyle(DWORD styles);
		inline void setImageList(HIMAGELIST list);
		inline void setItem(int i, TCITEM const& item);
		inline void setItemExtra(int extraBytes);
		inline void setItemSize(int x, int y);
		inline void setMinTabWidth(int x);
		inline void setPadding(int cx, int cy);
		inline void setToolTips(HWND tooltip);
		inline void setUnicodeFormat(BOOL unicode);

		//Constants
		constexpr static auto ClassName = WC_TABCONTROL;
	};

    Tab::Tab(HWND parent)
    {
		
        auto const rcClient = GetClientRect(parent);
        m_hwnd = CreateWindow(
            ClassName,
            L"",
            WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
            0, 0, rcClient.right, rcClient.bottom,
            parent,
            nullptr,
            gHinst,
            nullptr);

    }

    void Tab::addTab(int index, TCITEM const& item)
    {
        TabCtrl_InsertItem(m_hwnd, index, &item);
    }

    void Tab::addTab(int index, LPCTSTR text)
    {
        TCITEM item
        {
            .mask = TCIF_TEXT,
            .pszText = const_cast<LPTSTR>(text),
            .cchTextMax = static_cast<int>(StringLength(text))
        };
        addTab(index, item);
    }

    void Tab::adjustRect(BOOL larger, RECT& rect)
    {
        TabCtrl_AdjustRect(m_hwnd, larger, &rect);
    }

    void Tab::deleteAllItems()
    {
        TabCtrl_DeleteAllItems(m_hwnd);
    }

    void Tab::deleteItem(int i)
    {
        TabCtrl_DeleteItem(m_hwnd, i);
    }

    void Tab::deselectAll(UINT excludeFocus)
    {
        TabCtrl_DeselectAll(m_hwnd, excludeFocus);
    }

    int Tab::getCurFocus()
    {
        return TabCtrl_GetCurFocus(m_hwnd);
    }

    int Tab::getCurSel() const
    {
        return TabCtrl_GetCurSel(m_hwnd);
    }
    DWORD Tab::getExtendedStyle()
    {
        return TabCtrl_GetExtendedStyle(m_hwnd);
    }
    HIMAGELIST Tab::getImageList()
    {
        return TabCtrl_GetImageList(m_hwnd);
    }
    TCITEM Tab::getItem(int iItem, UINT mask)
    {
        TCITEM item
        {
            .mask = mask
        };
        TabCtrl_GetItem(m_hwnd, iItem, &item);
        return item;
    }
    int Tab::getItemCount()
    {
        return TabCtrl_GetItemCount(m_hwnd);
    }
    RECT Tab::getItemRect(int i)
    {
        RECT rc{};
        TabCtrl_GetItemRect(m_hwnd, i, &rc);
        return rc;
    }
    int Tab::getRowCount()
    {
        return TabCtrl_GetRowCount(m_hwnd);
    }
    HWND Tab::getToolTips()
    {
        return TabCtrl_GetToolTips(m_hwnd);
    }
    BOOL Tab::getUnicodeFormat()
    {
        return TabCtrl_GetUnicodeFormat(m_hwnd);
    }
    void Tab::highlightItem(int i, WORD highlight)
    {
        TabCtrl_HighlightItem(m_hwnd, i, highlight);
    }
    int Tab::hitTest(TCHITTESTINFO const& info)
    {
        return TabCtrl_HitTest(m_hwnd, &info);
    }
    void Tab::removeImage(int i)
    {
        TabCtrl_RemoveImage(m_hwnd, i);
    }
    void Tab::setCurFocus(int i)
    {
        TabCtrl_SetCurFocus(m_hwnd, i);
    }
    void Tab::setExtendedStyle(DWORD styles)
    {
        TabCtrl_SetExtendedStyle(m_hwnd, styles);
    }
    void Tab::setImageList(HIMAGELIST list)
    {
        TabCtrl_SetImageList(m_hwnd, list);
    }
    void Tab::setItem(int i, TCITEM const& item)
    {
        TabCtrl_SetItem(m_hwnd, i, &item);
    }
    void Tab::setItemExtra(int extraBytes)
    {
        TabCtrl_SetItemExtra(m_hwnd, extraBytes);
    }
    void Tab::setItemSize(int x, int y)
    {
        TabCtrl_SetItemSize(m_hwnd, x, y);
    }
    void Tab::setMinTabWidth(int x)
    {
        TabCtrl_SetMinTabWidth(m_hwnd, x);
    }
    void Tab::setPadding(int cx, int cy)
    {
        TabCtrl_SetPadding(m_hwnd, cx, cy);
    }
    void Tab::setToolTips(HWND tooltip)
    {
        TabCtrl_SetToolTips(m_hwnd, tooltip);
    }
    void Tab::setUnicodeFormat(BOOL unicode)
    {
        TabCtrl_SetUnicodeFormat(m_hwnd, unicode);
    }
}

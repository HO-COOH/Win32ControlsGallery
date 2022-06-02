#pragma once
#include "Controls.Control.hpp"
namespace Controls
{
	class TreeView : public Control
	{
	public:
		//Constants
		constexpr static auto ClassName = WC_TREEVIEW;

		enum class Style
		{
			Checkboxes = TVS_CHECKBOXES,
			
		};

		TreeView() = default;
		
		TreeView(HWND parent, DWORD style, int x, int y, int width, int height)
		{
			m_hwnd = CreateWindowEx(0, ClassName, L"", style, x, y, width, height, parent, NULL, NULL, NULL);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_createdragimage
		//wrong return value
		auto createDragImage(HTREEITEM item)
		{
			TreeView_CreateDragImage(m_hwnd, item);
		}
		
		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_deleteallitems
		void deleteAllItems()
		{
			TreeView_DeleteAllItems(m_hwnd);
		}

		auto deleteItem(HTREEITEM item)
		{
			TreeView_DeleteItem(m_hwnd, item);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_editlabel
		//wrong return value
		auto editLabel(HTREEITEM item)
		{
			return TreeView_EditLabel(m_hwnd, item);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_editlabel
		//wrong return value
		auto endEditLabel(bool cancel)
		{
			TreeView_EndEditLabelNow(m_hwnd, cancel);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_ensurevisible
		//wrong return value
		auto ensureVisible(HTREEITEM item)
		{
			TreeView_EnsureVisible(m_hwnd, item);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_expand
		//wrong return value
		void expand(HTREEITEM item, UINT code)
		{
			TreeView_Expand(m_hwnd, item, code);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getbkcolor
		//wrong return value
		auto getBkColor() const
		{
			return TreeView_GetBkColor(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getcheckstate
		//wrong return value
		auto getCheckState(HTREEITEM item) const
		{
			return TreeView_GetCheckState(m_hwnd, item);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getcheckstate
		//wrong return value
		auto getChild(HTREEITEM item) const
		{
			return TreeView_GetChild(m_hwnd, item);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getcount
		//wrong return value
		auto getCount() const
		{
			return TreeView_GetCount(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getdrophilight
		//wrong return value
		auto getDropHilight()
		{
			return TreeView_GetDropHilight(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getdrophilight
		//wrong return value
		auto getEditControl()
		{
			return TreeView_GetEditControl(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_geteditcontrol
		//wrong return value
		auto getExtendedStyle()
		{
			return TreeView_GetExtendedStyle(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getfirstvisible
		//wrong return value
		auto getFirstVisible()
		{
			return TreeView_GetFirstVisible(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getimagelist
		//wrong return value
		auto getImageList(INT imageType)
		{
			return TreeView_GetImageList(m_hwnd, imageType);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getindent
		//wrong return value
		auto getIndent()
		{
			return TreeView_GetIndent(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getinsertmarkcolor
		//wrong return value
		auto getInsertMarkColor()
		{
			return TreeView_GetInsertMarkColor(m_hwnd);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getisearchstring
		//wrong return value
		auto getISearchString(LPTSTR buffer)
		{
			return TreeView_GetISearchString(m_hwnd, buffer);
		}

		//doc bug: https://docs.microsoft.com/en-us/windows/win32/api/commctrl/nf-commctrl-treeview_getitem
		//wrong return value
		auto getItem(TVITEM& item)
		{
			return TreeView_GetItem(m_hwnd, &item);
		}

		//doc bug: 
	};
}
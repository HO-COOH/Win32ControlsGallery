#pragma once
#include "Gallery.Slider.h"
#include "Gallery.TabPageBase.h"
#include "Gallery.RadioButtonGroup.h"
#include "Gallery.Button.h"
#include <Controls.TextEdit.hpp>
#include <Controls.TreeView.hpp>
#include <ShObjIdl_core.h>
#include <atlbase.h>

namespace Gallery::Pages::ShellPage
{
	
	
	class TaskbarProgressStateRadioButton : public RadioButton
	{
		TBPFLAG const m_flag;
		
	public:
		
		TaskbarProgressStateRadioButton(HWND parent, LPCTSTR text, 
			int x, int y, int width, int height, TBPFLAG flag);

		~TaskbarProgressStateRadioButton()
		{
			OutputDebugString(L"Destroyed\n");
		}

		auto const getFlag() const { return m_flag; }
	};

	class Page : public TabPageBase
	{
		Slider m_taskbarProgressSlider;
		RadioButtonGroup<TaskbarProgressStateRadioButton> m_progressStates;
		
		ButtonEx m_makeTaskbarIcon;
		ButtonEx m_removeTaskbarIcon;
		ButtonEx m_makeNotification;
		bool m_added{};
		
		//taskbar jumplist with text edit
		Controls::TextEdit m_jumpListContent;
		Controls::TreeView m_jumpList;
		
		//toast notification

		
		//icon overlay
	
	public:
		Page(HWND container);

	};
}
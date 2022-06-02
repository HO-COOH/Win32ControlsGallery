#include "pch.h"
#include "Gallery.Pages.ShellPage.Page.h"
#include <Util.Error.hpp>
#include <UI.Shell.hpp>
#include "Resource.h"

static int row = 3;
static constexpr auto height = 50;
static constexpr auto width = 500;
extern HWND gHwnd;

namespace Gallery::Pages::ShellPage
{
    static CComPtr<ITaskbarList3> m_taskbarApi;
    TaskbarProgressStateRadioButton::TaskbarProgressStateRadioButton(
        HWND parent, LPCTSTR text, int x, int y, int width, int height, TBPFLAG flag) :
        RadioButton{ parent, text, x, y, width, height },
        m_flag{ flag }
    {

    }

    static NOTIFYICONDATA GetNotifyData(bool notify = false)
    {
        return NOTIFYICONDATA
        {
            .cbSize = sizeof(NOTIFYICONDATA),
            .hWnd = gHwnd,
            .uID = 0,
            .uFlags = static_cast<UINT>(notify ? NIF_ICON | NIF_INFO | NIF_TIP : NIF_ICON | NIF_TIP),
            .hIcon = LoadIcon(gHinst, MAKEINTRESOURCE(IDI_CORE)),
            .szTip = L"tip",
            .szInfo = L"A null-terminated string that specifies the text to display in a balloon notification. ",
            .uVersion = NOTIFYICON_VERSION_4,
            .szInfoTitle = L"Title (if this is empty, icon is not shown)",
            .dwInfoFlags = NIIF_INFO
        };
    }

    Gallery::Pages::ShellPage::Page::Page(HWND container) :
        TabPageBase{ container, L"Shell" },
        m_taskbarProgressSlider{ m_container, true, 0, 0, 300, 100 },
        m_progressStates
        {
            std::vector{
                TaskbarProgressStateRadioButton{m_container, L"TBPF_NOPROGRESS", 0, row++ * height, width, height, TBPF_NOPROGRESS,},
                TaskbarProgressStateRadioButton{m_container, L"TBPF_INDETERMINATE", 0, row++ * height, width, height, TBPF_INDETERMINATE},
                TaskbarProgressStateRadioButton{m_container, L"TBPF_NORMAL", 0, row++ * height, width, height, TBPF_NORMAL},
                TaskbarProgressStateRadioButton{m_container, L"TBPF_ERROR", 0, row++ * height, width, height, TBPF_ERROR},
                TaskbarProgressStateRadioButton{m_container, L"TBPF_PAUSED", 0, row++ * height, width, height, TBPF_PAUSED}
            }
        },
		m_makeTaskbarIcon{m_container, static_cast<DWORD>(Controls::Button::Style::PushButton), 0, (row++ ) * height, width, height},
		m_removeTaskbarIcon{m_container, static_cast<DWORD>(Controls::Button::Style::PushButton), 0, row++ * height, width, height},
		m_makeNotification{m_container, static_cast<DWORD>(Controls::Button::Style::PushButton), 0, row++ * height, width, height},
        m_jumpListContent{m_container, static_cast<DWORD>(Controls::TextEdit::Styles::Center) | static_cast<DWORD>(Controls::TextEdit::Styles::AutoHScroll) | WS_BORDER, 500, height, 200, height}
    {
        CheckRet(m_taskbarApi.CoCreateInstance(CLSID_TaskbarList));

        CheckRet(m_taskbarApi->SetProgressState(gHwnd, TBPF_NORMAL));
        m_taskbarProgressSlider.setRange(0, 100);
        m_taskbarProgressSlider.setPos(true, 50);
        m_taskbarProgressSlider.onPositionChange(
            [this]()
            {
                auto const pos = m_taskbarProgressSlider.getPos();
                //set progress on taskbar
                CheckRet(m_taskbarApi->SetProgressValue(gHwnd, pos, 100));
            }
        ); 

        
        for (int i = 0; i < 5; ++i)
        {
            auto& button = m_progressStates[i];
            button.onClick([&button](HWND)
                {
                    if (button.isChecked())
                        m_taskbarApi->SetProgressState(gHwnd, button.getFlag());
                    else
                        m_taskbarApi->SetProgressState(gHwnd, TBPF_NOPROGRESS);
                });
        }
        m_progressStates.addHandler();


        m_makeTaskbarIcon.setText(L"Make taskbar icon");
        m_removeTaskbarIcon.setText(L"Remove taskbar icon");
        m_makeNotification.setText(L"Make notification");
        m_makeTaskbarIcon.onClick([this](HWND)
        {
            if (m_added)
                return;
            
            static auto data = GetNotifyData(false);
            UI::Shell::NotifyIcon(UI::Shell::NotifyIconMethod::Add, data);
            m_added = true;
        });

        m_removeTaskbarIcon.onClick([this](HWND)
        {
            if (!m_added)
                return;
			
            static auto data = GetNotifyData(false);
            UI::Shell::NotifyIcon(UI::Shell::NotifyIconMethod::Delete, data);
            m_added = false;
        });

        m_makeNotification.onClick([this](HWND)
        {
            static auto data = GetNotifyData(true);
            UI::Shell::NotifyIcon(m_added ? UI::Shell::NotifyIconMethod::Mofidy : UI::Shell::NotifyIconMethod::Add, data);
            m_added = true;
        });
        
    }
}



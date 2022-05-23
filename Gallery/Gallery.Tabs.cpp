#include "pch.h"
#include "Gallery.Tabs.h"
#include "Gallery.MainWindow.h"

extern HINSTANCE gHinst;
namespace Gallery
{
    void Tabs::addHandler()
    {
        OnSelectionChangeHandlers.add(getHandle(), [this](NMHDR const* info)
        {
            getCurrentShowingPage()->hide();
            auto const currentSelection = getCurSel();
            m_pages[currentSelection]->show();
            setCurrentShowingPage(currentSelection);
        });

        //TODO: handle resizing of the main window
    }

    void Tabs::setCurrentShowingPage(int selection)
    {
        m_currentShowingPage = selection;
    }

    void Tabs::RegisterContainer()
    {
        static bool registered = false;
        if (registered)
            return;

        WNDCLASSEXW wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = +[](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
        { 
            switch (message)
            {
                case WM_NOTIFY:
                case WM_COMMAND:
                    return MainWindow::WndProc(hWnd, message, wParam, lParam);
            }
            return DefWindowProc(hWnd, message, wParam, lParam); 
        };
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = gHinst;
        wcex.hIcon = NULL;
        wcex.hCursor = NULL;
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = L"container";
        wcex.hIconSm = NULL;
        RegisterClassExW(&wcex);

        registered = true;
    }
	
    Tabs::Tabs(HWND parent, std::vector<std::unique_ptr<PageBase>> pages) :
        Controls::Tab(parent),
        m_pages(std::move(pages))
    {
        int i = 0;
        for (auto& page : m_pages)
            addTab(i++, page->getName().data());
        addHandler();
    }

    Tabs::Tabs(HWND parent) : Controls::Tab(parent)
    {
        addHandler();
    }
	
    Tabs& Tabs::operator+=(std::unique_ptr<PageBase>&& page)
    {
        m_pages.emplace_back(std::move(page));

        addTab(m_pages.size() - 1, m_pages.back()->getName().data());
        m_currentShowingPage = m_pages.size() - 1;
		
        m_pages.back()->show();
        return *this;
    }
    std::unique_ptr<PageBase>& Tabs::getCurrentShowingPage()
    {
        assert(m_currentShowingPage != -1);
        return m_pages[m_currentShowingPage];
    }
    HWND Tabs::getContainerWindow()
    {
        RegisterContainer();
        RECT rect{};
        auto const handle = getHandle();
        GetClientRect(handle, &rect);
        adjustRect(FALSE, rect);
		//TODO: fix high dpi
        rect.top += 25;
        rect.bottom = 2000;
        return CreateWindow(L"container", L"", WS_CHILD, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, handle, NULL, NULL, NULL);
    }
}
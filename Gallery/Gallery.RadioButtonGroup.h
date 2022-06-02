#pragma once
#include <type_traits>
#include <vector>
#include "Gallery.Button.h"

#include <string>

namespace Gallery
{
    template<typename T>
    concept IRadioButton = std::is_base_of_v<Gallery::RadioButton, T>;
    
    template<IRadioButton T>
    class RadioButtonGroup
    {
        std::vector<T> m_radioButtons;

        void onElementCheck(T& element)
        {
            for (auto& radioButton : m_radioButtons)
            {
                if (&radioButton != &element)
                {
                    radioButton.setCheckNoop(false);
                }
            }
        }
    public:
        RadioButtonGroup(std::vector<T> radioButtons) : m_radioButtons{ std::move(radioButtons) }
        {
        }

        void addHandler()
        {
            for (auto& radioButton : m_radioButtons)
            {
                auto oldHandler = radioButton.OnClickHandlers.get(radioButton.getHandle());
                OutputDebugString(std::to_wstring(radioButton.isChecked()).c_str());
                radioButton.newOnClick([&radioButton, this, oldHandler](HWND hwnd)
                    {
                        oldHandler(hwnd);
                        if (radioButton.isChecked())
                            onElementCheck(radioButton);
                    });
            }
        }

        auto& operator[](size_t i)
        {
            return m_radioButtons[i];
        }
    };

}
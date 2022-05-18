#pragma once
#include <type_traits>
#include <vector>
#include "Gallery.Button.h"
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
        template<size_t N>
        RadioButtonGroup(T(&& radioButtons)[N]) :
            m_radioButtons(std::make_move_iterator(std::begin(radioButtons)), std::make_move_iterator(std::end(radioButtons)))
        {
            for (auto& radioButton : m_radioButtons)
            {
                radioButton.onClick([this, &radioButton](HWND) mutable
                {
                    if (radioButton.isChecked())
                        onElementCheck(radioButton);
                });
            }
        }

        
    };

}
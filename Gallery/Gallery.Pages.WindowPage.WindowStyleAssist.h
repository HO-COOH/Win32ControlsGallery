#pragma once
#include "Gallery.Pages.WindowPage.WindowStyleCheckbox.h"
#include <thread>
#include <vector>
#include <memory>
#include <queue>


namespace Gallery::Pages::WindowPage
{
    constexpr auto inline NumFlashes = 3;
    constexpr auto inline FlashDuration = 150; //milliseconds
    //struct FlashingObject
    //{
    //    WindowStyleCheckbox* checkbox{};
    //    int numFlashes = NumFlashes;

    //};


    class Relation
    {
    public:
        std::chrono::steady_clock::time_point m_lastExecute;
        virtual void execute() = 0;
        bool needWait() const;
    };

    /**
     * @brief Indicating Style[A] == Style[B]
    */
    class EquivalentRelation : public Relation
    {
        std::vector<WindowStyleCheckbox*> m_checkbox;
        std::queue<Relation*>* queueRef{};
        int m_times = NumFlashes;
        
    public:
        EquivalentRelation() = default;
        EquivalentRelation(std::vector<WindowStyleCheckbox*> checkbox)
            : m_checkbox{ std::move(checkbox) }
        {
        }

        EquivalentRelation& operator+=(WindowStyleCheckbox& checkbox)
        {
            m_checkbox.push_back(&checkbox);
            return *this;
        }

        void execute() override
        {
            while (m_times--)
            {
                for (auto& checkbox : m_checkbox)
                    checkbox->setCheckNoop(true);
                std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
                for (auto& checkbox : m_checkbox)
                    checkbox->setCheck(false);
                std::this_thread::sleep_for(std::chrono::milliseconds{ 150 });
            }
        }

        void setCheck(bool check)
        {
            for (auto& checkbox : m_checkbox)
                checkbox->setCheck(check);
        }
    };

    /**
     * @brief Indicating setting Style[A] must also set Style[B]
    */
    class RequirementRelation : public Relation
    {
        WindowStyleCheckbox* m_primary;
        std::vector<WindowStyleCheckbox*> m_requirement;
    public:
        RequirementRelation(WindowStyleCheckbox& primary)
            : m_primary{ &primary }
        {
        }

        RequirementRelation(WindowStyleCheckbox& primary, std::vector<WindowStyleCheckbox*> requirments)
            : m_primary{ &primary }, m_requirement{ std::move(requirments) }
        {
        }

        RequirementRelation& operator+=(WindowStyleCheckbox& checkbox)
        {
            m_requirement.push_back(&checkbox);
            return *this;
        }

        void execute() override
        {
            throw std::exception{};
        }

    };

    /**
     * @brief Indicating Style[A] cannot be combined with Style[B]
    */
    class ExclusiveRelation : public Relation
    {
    public:

    };

	

    
	class WindowStyleAssist
	{
        std::vector<std::unique_ptr<Relation>> m_relations;
        std::queue<Relation*> m_objects;
	    
        std::thread t
        {
            [this]
            {
                while (!m_objects.empty())
                {
                    m_objects.front()->execute();
                    if(m_objects.front()->needWait())
                    {
                        //std::this_thread::sleep_for(m_objects.front()->m_lastExecute + std::chrono::milliseconds{ FlashDuration });
                    }
                }
            }
        };
        void execute()
        {}
    public:
		WindowStyleAssist(std::vector<std::unique_ptr<Relation>> relations);
        ~WindowStyleAssist();//join t
	};
}
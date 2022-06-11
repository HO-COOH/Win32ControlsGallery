#pragma once
#include <unordered_map>
#include <functional>
#include <cassert>

template<typename Identifier, typename Function>
class Handler
{
    std::unordered_map<Identifier, std::function<Function>> m_handlers;
public:
    template<typename Handler>
    void add(Identifier id, Handler&& handler)
    {
        //m_handlers.emplace(id, std::forward<Handler>(handler));
        m_handlers[id] = std::move(handler);
    }

    void remove(Identifier id)
    {
        assert(m_handlers.erase(id) == 1);
    }

    auto& get(Identifier id)
    {
        return m_handlers.at(id);
    }

    template<typename Identifier, typename ... Args>
    auto call(Identifier id, Args&& ... args)
    {
        using ReturnType = decltype(m_handlers)::mapped_type::result_type;
        if constexpr (std::is_same_v<ReturnType, void>)
        {
            if (m_handlers.empty())
                return;

            auto it = m_handlers.find(id);
            if (it != m_handlers.end())
            {
                it->second(std::forward<Args>(args)...);
            }
            return;
        }
        else
        {
            if (m_handlers.empty())
                return ReturnType{};

            auto it = m_handlers.find(id);
            if (it != m_handlers.end())
            {
                return it->second(std::forward<Args>(args)...);
            }
            return ReturnType{};
        }
    }
};

template<typename Function>
class SingletonHandler
{
    Function handler;
public:
    void add(Function&& handler)
    {
        this->handler = handler;
    }

    void remove()
    {
        handler = {};
    }

    template<typename... Args>
    void call(Args&&... args)
    {
        if (handler)
            handler(std::forward<Args>(args)...);
    }
};

#include <unordered_set>
#include <cassert>
template<typename Identifier, typename Function>
class StaticHandler
{
    std::unordered_set<Identifier> m_objects;
    Function m_handler;
public:
	
    StaticHandler(Function&& function) : m_handler{ std::forward<Function>(function) }
    {
    }

	template<typename Handler>
    void add(Identifier id, Handler&& handler)
    {
        assert(!m_objects.contains(id));
        m_objects.emplace(id);
    }

    void remove(Identifier id)
    {
        m_objects.erase(id);
    }

    template<typename Identifier, typename ... Args>
    void call(Identifier id, Args&& ... args)
    {
        std::invoke(m_handler, std::forward<Args>(args)...);
    }
};
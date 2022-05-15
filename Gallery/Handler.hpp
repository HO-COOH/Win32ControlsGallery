#pragma once
#include <unordered_map>
#include <functional>

template<typename Identifier, typename Function>
class Handler
{
    std::unordered_map<Identifier, std::function<Function>> m_handlers;
public:
    template<typename Handler>
    void add(Identifier id, Handler&& handler)
    {
        m_handlers.emplace(id, std::forward<Handler>(handler));
    }

    void remove(Identifier id)
    {
        m_handlers.erase(id);
    }

    template<typename Identifier, typename ... Args>
    void call(Identifier id, Args&& ... args)
    {
        if (m_handlers.empty())
            return;

        auto it = m_handlers.find(id);
        if (it != m_handlers.end())
        {
            it->second(std::forward<Args>(args)...);
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
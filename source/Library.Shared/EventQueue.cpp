#include "pch.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
    void EventQueue::Enqueue(std::shared_ptr<EventPublisher> e, std::chrono::duration<int, std::ratio<1, 1000>> t)
    {
        e->SetTime(GameState::Instance()->Time().CurrentTime() + t);
        _events.PushBack(e);
    }
    void EventQueue::Update(GameTime g)
    {
        SList<std::shared_ptr<EventPublisher>> eventCopy(_events);
        for (auto i = eventCopy.begin(); i != eventCopy.end(); i++)
        {
            if (g.CurrentTime() >= (*i)->GetTime())
            {
                (*i)->Deliver();
                _events.Remove(*i);
            }
        }
    }
    void EventQueue::Clear()
    {
        _events.Clear();
    }
    bool EventQueue::IsEmpty()
    {
        return _events.IsEmpty();
    }
    size_t EventQueue::Size()
    {
        return _events.Size();
    }
}
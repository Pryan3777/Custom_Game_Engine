#include "pch.h"
#include "EventPublisher.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);

	EventPublisher::EventPublisher(SList<EventSubscriber*> &subscribers) :
		_subscribers(subscribers)
	{
	}

	EventPublisher& EventPublisher::operator=(const EventPublisher& other)
	{
		if (this != &other)
		{
			_subscribers = other._subscribers;
			_expirationTime = other._expirationTime;
		}
		return *this;
	}

	void EventPublisher::Deliver()
	{
		SList<EventSubscriber*> s(_subscribers);
		for (auto i = s.begin(); i != s.end(); i++)
		{
			(*i)->Notify(this);
		}
	}
	std::string EventPublisher::ToString() const
	{
		return std::string();
	}
	bool EventPublisher::Equals(const RTTI*) const
	{
		return false;
	}
	void EventPublisher::SetTime(std::chrono::high_resolution_clock::time_point t)
	{
		_expirationTime = t;
	}
	std::chrono::high_resolution_clock::time_point EventPublisher::GetTime() const
	{
		return _expirationTime;
	}
}
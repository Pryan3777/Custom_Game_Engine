#pragma once

#include "Event.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	template <typename T>
	RTTI_DEFINITIONS(Event<T>);

	template<typename T>
	Event<T>::Event(T& message) :
		EventPublisher(_subscribers),
		_message(message)
	{

	}

	template<typename T>
	inline Event<T>& Event<T>::operator=(const Event<T>& other)
	{
		if (this != &other)
		{
			_message = other._message;
		}
		return *this;
	}

	template<typename T>
	inline void Event<T>::Subscribe(EventSubscriber* subscriber)
	{
		if (_subscribers.Find(subscriber) == _subscribers.end())
		{
			_subscribers.PushBack(subscriber);
		}
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(EventSubscriber* subscriber)
	{
		auto i = _subscribers.Find(subscriber);
		if (i != _subscribers.end())
		{
			_subscribers.Remove(i);
		}
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		_subscribers.Clear();
	}

	template<typename T>
	inline bool Event<T>::Equals(const RTTI* other) const
	{
		if (other == nullptr)
		{
			return false;
		}
		return _message == other->As<Event<T>>()->_message;
	}

	template<typename T>
	inline T Event<T>::Message()
	{
		return _message;
	}

}
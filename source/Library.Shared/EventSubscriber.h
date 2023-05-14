#pragma once

namespace FieaGameEngine
{
	class EventPublisher;

	class EventSubscriber
	{
	protected:
		virtual ~EventSubscriber() = default;

	public:
		virtual void Notify(EventPublisher* event) = 0;
	};
}
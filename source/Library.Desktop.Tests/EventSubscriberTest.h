#pragma once
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "Event.h"
#include "RTTI.h"

using namespace FieaGameEngine;
namespace UnitTests
{
	class EventSubscriberTest : public EventSubscriber
	{
	public:
		EventSubscriberTest() = default;
		~EventSubscriberTest() {};

		virtual void Notify(EventPublisher* p) override;

		int _timesCalled = 0;
		int _mostRecentMessage = 0;
	};
}
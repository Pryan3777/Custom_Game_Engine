#include "pch.h"
#include "EventSubscriberTest.h"



using namespace FieaGameEngine;
namespace UnitTests
{
	void EventSubscriberTest::Notify(EventPublisher* p)
	{
		++_timesCalled;
		_mostRecentMessage = p->As<Event<int>>()->Message();
	}
}


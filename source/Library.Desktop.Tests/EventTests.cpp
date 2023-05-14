#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "TypeManager.h"
#include "EventSubscriberTest.h"
#include "EventQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace LibraryDesktopTests
{
	TEST_CLASS(EventTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

			GameState::CreateInstance();
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			EventQueue::Clear();
			Event<int>::UnsubscribeAll();
			GameState::DestroyInstance();


#if defined(DEBUG) || defined(_DEBUG)
			_CrtDumpMemoryLeaks();
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(BasicEvent)
		{
			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());

			auto eventSubscriber = new EventSubscriberTest();

			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			GameTime g;
			int i = 2;

			auto e = std::make_shared<Event<int>>(i);

			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(0));

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());

			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(0));

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			EventQueue::Update(g);
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);

			delete eventSubscriber;
		}
		TEST_METHOD(DelayedEvent)
		{
			auto eventSubscriber = new EventSubscriberTest();
			GameTime g;
			GameTime h(g);
			h.SetCurrentTime(h.CurrentTime() + 1s);
			int i = 2;

			auto e = std::make_shared<Event<int>>(i);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			g.SetCurrentTime(g.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);

			delete eventSubscriber;
		}
		TEST_METHOD(CopyOperator)
		{
			auto eventSubscriber = new EventSubscriberTest;
			GameTime g;
			GameTime h(g);
			h.SetCurrentTime(h.CurrentTime() + 1s);
			int i = 2;

			Event<int> baseEvent(i);
			auto e = std::make_shared<Event<int>>(baseEvent);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			g.SetCurrentTime(g.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);

			delete eventSubscriber;
		}
		TEST_METHOD(CopyAssignmentOperator)
		{
			auto eventSubscriber = new EventSubscriberTest();
			GameTime g;
			GameTime h(g);
			h.SetCurrentTime(h.CurrentTime() + 1s);
			int i = 2;

			Event<int> baseEvent(i);
			Event<int> copiedEvent(i);
			copiedEvent = baseEvent;

			Assert::IsTrue(baseEvent.Equals(&copiedEvent));

			auto e = std::make_shared<Event<int>>(copiedEvent);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			g.SetCurrentTime(g.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);

			delete eventSubscriber;
		}
		TEST_METHOD(MoveOperator)
		{
			auto eventSubscriber = new EventSubscriberTest();
			GameTime g;
			GameTime h(g);
			h.SetCurrentTime(h.CurrentTime() + 1s);
			int i = 2;

			Event<int> baseEvent(i);
			Event<int> copiedEvent(std::move(baseEvent));

			auto e = std::make_shared<Event<int>>(copiedEvent);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int,std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			g.SetCurrentTime(g.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);
			delete eventSubscriber;
		}
		TEST_METHOD(MoveAssignmentOperator)
		{
			auto eventSubscriber = new EventSubscriberTest();
			GameTime g;
			GameTime h(g);
			h.SetCurrentTime(h.CurrentTime() + 1s);
			int i = 2;

			Event<int> baseEvent(i);
			Event<int> copiedEvent(i);
			copiedEvent = std::move(baseEvent);

			auto e = std::make_shared<Event<int>>(copiedEvent);

			Event<int>::Subscribe(eventSubscriber);
			EventQueue::Enqueue(e, std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(1), EventQueue::Size());
			Assert::AreEqual(false, EventQueue::IsEmpty());
			Assert::AreEqual(0, eventSubscriber->_timesCalled);
			Assert::AreEqual(0, eventSubscriber->_mostRecentMessage);

			g.SetCurrentTime(g.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			EventQueue::Update(g);

			Assert::AreEqual(size_t(0), EventQueue::Size());
			Assert::AreEqual(true, EventQueue::IsEmpty());
			Assert::AreEqual(1, eventSubscriber->_timesCalled);
			Assert::AreEqual(2, eventSubscriber->_mostRecentMessage);

			delete eventSubscriber;
		}


	private:
		_CrtMemState _startMemState;
	};
};
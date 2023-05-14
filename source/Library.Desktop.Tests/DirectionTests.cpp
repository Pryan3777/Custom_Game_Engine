#include "pch.h"
#include "DirectionVectors.h"
#include "CppUnitTest.h"
#include <cassert>
#include "memory"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(DirectionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
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

		TEST_METHOD(ForwardCaseOne)
		{
			std::pair<Direction, Direction> p = std::make_pair(Direction::X, Direction::Y);
			MovementCase c = MovementCase::Up;

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::nY == p.first);
			Assert::IsTrue(Direction::X == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::nX == p.first);
			Assert::IsTrue(Direction::nY == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::Y == p.first);
			Assert::IsTrue(Direction::nX == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Y == p.second);
		}

		TEST_METHOD(ForwardCaseTwo)
		{
			std::pair<Direction, Direction> p = std::make_pair(Direction::X, Direction::Y);
			MovementCase c = MovementCase::Forward;

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Y == p.second);
		}

		TEST_METHOD(ForwardCaseThree)
		{
			std::pair<Direction, Direction> p = std::make_pair(Direction::X, Direction::Y);
			MovementCase c = MovementCase::Down;

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::Y == p.first);
			Assert::IsTrue(Direction::nX == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::nX == p.first);
			Assert::IsTrue(Direction::nY == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::nY == p.first);
			Assert::IsTrue(Direction::X == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Y == p.second);
		}

		TEST_METHOD(Turning)
		{
			std::pair<Direction, Direction> p = std::make_pair(Direction::X, Direction::Y);
			MovementCase c = MovementCase::Down;

			p.second = Left(p.first, p.second);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Z == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::Z == p.first);
			Assert::IsTrue(Direction::nX == p.second);

			p.second = Left(p.first, p.second);

			Assert::IsTrue(Direction::Z == p.first);
			Assert::IsTrue(Direction::nY == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::nY == p.first);
			Assert::IsTrue(Direction::nZ == p.second);

			p.second = Left(p.first, p.second);

			Assert::IsTrue(Direction::nY == p.first);
			Assert::IsTrue(Direction::X == p.second);

			p = Forward(p.first, p.second, c);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Y == p.second);

			p.second = Left(p.first, p.second);
			p.second = Right(p.first, p.second);

			Assert::IsTrue(Direction::X == p.first);
			Assert::IsTrue(Direction::Y == p.second);
		}


	private:
		_CrtMemState _startMemState;
	};
};
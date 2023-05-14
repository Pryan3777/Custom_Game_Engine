#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "DefaultHash.h"
#include "Foo.h"
#include "UserHashImplementation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}
}

namespace LibraryDesktopTests
{
	TEST_CLASS(DefaultHashTests)
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
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(Int)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			DefaultHash<int> hashFunc;

			Assert::AreEqual(hashFunc(a), hashFunc(a));
			Assert::AreNotEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(b), hashFunc(c));
			Assert::AreEqual(hashFunc(a), hashFunc(c));
		}
		TEST_METHOD(CharStar)
		{
			std::string as = "test"s;
			std::string bs = "testB"s;
			std::string cs = "test"s;

			char* a = as.data();
			char* b = bs.data();
			char* c = cs.data();

			DefaultHash<char*> hashFunc;

			Assert::AreEqual(hashFunc(a), hashFunc(a));
			Assert::AreNotEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(b), hashFunc(c));
			Assert::AreEqual(hashFunc(a), hashFunc(c));
		}
		TEST_METHOD(String)
		{
			std::string a = "test"s;
			std::string b = "testB"s;
			std::string c = "test"s;

			DefaultHash<std::string> hashFunc;

			Assert::AreEqual(hashFunc(a), hashFunc(a));
			Assert::AreNotEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(b), hashFunc(c));
			Assert::AreEqual(hashFunc(a), hashFunc(c));
		}
		TEST_METHOD(FooTest)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(10);

			DefaultHash<const Foo> hashFunc;

			Assert::AreEqual(hashFunc(a), hashFunc(a));
			Assert::AreNotEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(b), hashFunc(c));
			Assert::AreEqual(hashFunc(a), hashFunc(c));
		}
	private:
		_CrtMemState _startMemState;
	};
}
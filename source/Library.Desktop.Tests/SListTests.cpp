#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "Foo.h"

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

	template<>
	std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& t)
	{
		wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	/*template<>
	std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& t)
	{
		wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}*/
}

namespace LibraryDesktopTests
{
	TEST_CLASS(SListTests)
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

		TEST_METHOD(Constructor)
		{
			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); front; });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); back; });
		}

		TEST_METHOD(CopySemantics)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(30);
			
			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(c, list.Back());
			{
				SList<Foo> copyOfList{ list };
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}
			{
				SList<Foo> copyOfList;
				copyOfList.PushBack(b);
				copyOfList = {list};
				Assert::AreEqual(size_t(3), list.Size());
				Assert::AreEqual(a, copyOfList.Front());
				Assert::AreEqual(c, copyOfList.Back());
			}
			{
				SList<Foo> copyOfList{ list };
				const Foo d = list.Front();
				const Foo e = list.Back();
			}
		}

		TEST_METHOD(PushAndPop)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(30);

			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());

			Assert::ExpectException<std::runtime_error>([&list]() {list.PopFront();});
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopBack(); });

			list.PushBack(b);
			Assert::AreEqual(b, list.Front());
			Assert::AreEqual(b, list.Back());
			Assert::AreEqual(size_t(1), list.Size());

			list.PushFront(a);
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(b, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PushBack(c);
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(c, list.Back());
			Assert::AreEqual(size_t(3), list.Size());

			Assert::AreEqual(a, list.PopFront());
			Assert::AreEqual(b, list.Front());
			Assert::AreEqual(c, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PushFront(a);
			Assert::AreEqual(c, list.PopBack());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(b, list.Back());
			Assert::AreEqual(size_t(2), list.Size());

			list.PopBack();
			list.PopBack();
			Assert::AreEqual(size_t(0), list.Size());
		}
		TEST_METHOD(ClearAndIsEmpty)
		{
			const Foo a(10);

			SList<Foo> list;
			Assert::AreEqual(true, list.IsEmpty());
			Assert::AreEqual(size_t(0), list.Size());

			list.PushFront(a);
			list.PushFront(a);
			Assert::AreEqual(false, list.IsEmpty());

			list.Clear();
			Assert::AreEqual(true, list.IsEmpty());
		}
		TEST_METHOD(SListConst)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(30);

			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);

			const SList<Foo> constList = list;
			Assert::AreEqual(a, constList.Front());
			Assert::AreEqual(c, constList.Back());

			list.PopBack();
			list.PopBack();
			list.PopBack();

			const SList<Foo> constEmptyList = list;
			Assert::ExpectException<std::runtime_error>([&constEmptyList]() {auto& front = constEmptyList.Front(); front; });
			Assert::ExpectException<std::runtime_error>([&constEmptyList]() {auto& back = constEmptyList.Back(); back; });

		}
		TEST_METHOD(Iterator)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(30);

			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);

			SList<Foo>::Iterator itConstructor = SList<Foo>::Iterator(list);
			SList<Foo>::ConstIterator itConstConstructor = SList<Foo>::ConstIterator(list);

			SList<Foo>::Iterator it = SList<Foo>::Iterator(list);
			Assert::AreEqual(a, *it);
			it++;
			Assert::AreEqual(b, *it);
			++it;
			Assert::AreEqual(c, *it);
			it++;
			
			SList<Foo>::Iterator itBegin = list.begin();
			Assert::IsFalse(itBegin == it);
			Assert::IsTrue(itBegin != it);
			
			SList<Foo>::Iterator itEnd = list.end();
			Assert::IsTrue(itEnd == it);
			Assert::IsFalse(itEnd != it);
			
			SList<Foo> listCopy = list;
			it = listCopy.Find(b);
			Assert::AreEqual(b, *it);
			Assert::ExpectException<std::runtime_error>([it, list, a]() {SList<Foo> listCopyB = list;  listCopyB.InsertAfter(it,a); });
			
			listCopy.Remove(b);
			Assert::AreEqual(false, listCopy.Remove(b));
			Assert::AreEqual(listCopy.Size(), size_t(2));
			listCopy.Remove(c);
			Assert::AreEqual(listCopy.Size(), size_t(1));
			listCopy.Remove(a);
			Assert::AreEqual(listCopy.Size(), size_t(0));

			listCopy.PushFront(a);
			it = listCopy.begin();
			Assert::AreEqual(a, *it);
			auto itA = listCopy.end();
			auto itB = ++it;
			Assert::AreEqual(itA, itB);

			listCopy.Clear();
			it = listCopy.begin();
			listCopy.InsertAfter(it, a);
			it = listCopy.begin();
			listCopy.InsertAfter(it, c);
			listCopy.InsertAfter(it, b);
			Assert::AreEqual(a, *it);
			Assert::AreEqual(b, *++it);
			Assert::AreEqual(c, *++it);
			listCopy.Remove(c);
			listCopy.Remove(b);
			listCopy.Remove(a);
			Assert::AreEqual(size_t(0), listCopy.Size());

			Assert::ExpectException<std::runtime_error>([]() {SList<Foo> list;  SList<Foo>::Iterator it = list.end(); it++; });
			Assert::ExpectException<std::runtime_error>([]() {SList<Foo> list;  SList<Foo>::Iterator it = list.end(); ++it; });
		}
		TEST_METHOD(ConstIterator)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(30);
			Foo d(40);

			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);

			SList<Foo>::ConstIterator it = SList<Foo>::ConstIterator(list);
			Foo ConstFoo = *it;
			Assert::AreEqual(a, *it);
			it++;
			Assert::AreEqual(b, *it);
			++it;
			Assert::AreEqual(c, *it);
			it++;

			SList<Foo>::ConstIterator itBegin = list.begin();
			Assert::IsFalse(itBegin == it);
			Assert::IsTrue(itBegin != it);

			SList<Foo>::ConstIterator itEnd = list.end();
			Assert::IsTrue(itEnd == it);
			Assert::IsFalse(itEnd != it);

			const SList<Foo> listConst = list;
			SList<Foo>::ConstIterator itConst = listConst.cend();
			
			SList<Foo>::ConstIterator itBeginConst = listConst.begin();
			Assert::IsFalse(itBeginConst == itConst);
			Assert::IsTrue(itBeginConst != itConst);

			SList<Foo>::ConstIterator itEndConst = listConst.end();
			Assert::IsTrue(itEndConst == itConst);
			Assert::IsFalse(itEndConst != itConst);

			SList<Foo>::ConstIterator itFind = listConst.Find(b);
			Assert::AreEqual(b, *itFind);

			SList<Foo>::Iterator itNonConst = SList<Foo>::Iterator(list);
			SList<Foo>::ConstIterator itConstCopy = SList<Foo>::ConstIterator(itNonConst);
			SList<Foo>::ConstIterator itCopyDirect = SList<Foo>::ConstIterator(list);
			Assert::IsTrue(itConstCopy == itCopyDirect);

			SList<Foo>::ConstIterator itBeginC = list.cbegin();
			Assert::IsFalse(itBeginC == it);
			Assert::IsTrue(itBeginC != it);

			SList<Foo>::ConstIterator itEndC = list.cend();
			Assert::IsTrue(itEndC == it);
			Assert::IsFalse(itEndC != it);

			SList<Foo> listCopy;
			it = listCopy.cbegin();
			listCopy.InsertAfter(it, a);
			it = listCopy.cbegin();
			listCopy.InsertAfter(it, c);
			listCopy.InsertAfter(it, b);
			Assert::AreEqual(a, *it);
			Assert::AreEqual(b, *++it);
			Assert::AreEqual(c, *++it);
			listCopy.Remove(c);
			listCopy.Remove(b);
			listCopy.Remove(a);
			Assert::AreEqual(size_t(0), listCopy.Size());

			Assert::ExpectException<std::runtime_error>([a]() {SList<Foo> list;  SList<Foo> listWrong;  SList<Foo>::ConstIterator it = list.cbegin(); listWrong.InsertAfter(it, a); });
			Assert::ExpectException<std::runtime_error>([]() {SList<Foo> list;  SList<Foo>::ConstIterator it = list.cend(); *it; });
			Assert::ExpectException<std::runtime_error>([]() {SList<Foo> list;  SList<Foo>::ConstIterator it = list.cend(); it++; });
			Assert::ExpectException<std::runtime_error>([]() {SList<Foo> list;  SList<Foo>::ConstIterator it = list.cend(); ++it; });
		}
	private:
		_CrtMemState _startMemState;
	};
}

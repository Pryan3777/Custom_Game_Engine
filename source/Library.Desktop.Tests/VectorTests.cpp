#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
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
	std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& t)
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

	template<>
	std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& t)
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
}

namespace LibraryDesktopTests
{
	TEST_CLASS(VectorTests)
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
			Foo a(10);
			Foo b(20);
			Foo c(30);

			Vector<Foo> vec;
			vec.Reserve(size_t(2));

			vec.PushBack(a);
			Assert::AreEqual(size_t(1), vec.Size());
			vec.PushBack(b);
			Assert::AreEqual(size_t(2), vec.Size());
			vec.PushBack(c);
			Assert::AreEqual(size_t(3), vec.Size());

			Assert::AreEqual(vec[0], a);
			Assert::AreEqual(vec[1], b);
			Assert::AreEqual(vec[2], c);

			Assert::AreEqual(vec.At(0), a);
			Assert::AreEqual(vec.At(1), b);
			Assert::AreEqual(vec.At(2), c);

			Foo d = vec.Front();
			Assert::AreEqual(vec.Front(), a);
			Assert::AreEqual(vec.Back(), c);

			vec.PopBack();
			vec.PopBack();
			Assert::AreEqual(vec.Size(), size_t(1));
			Assert::AreEqual(vec.Capacity(), size_t(4));
			vec.Reserve(size_t(100));
			Assert::AreEqual(vec.Size(), size_t(1));
			Assert::AreEqual(vec.Capacity(), size_t(100));
			vec.ShrinkToFit();
			Assert::AreEqual(vec.Size(), size_t(1));
			Assert::AreEqual(vec.Capacity(), size_t(1));

			Assert::AreEqual(vec.IsEmpty(), false);
			vec.PopBack();
			Assert::AreEqual(vec.IsEmpty(), true);

			vec.PushBack(a);
			vec.PushBack(b);

			Vector<Foo> vecCopy(vec);
			Vector<Foo> vecAssign;
			vecAssign = vec;
			Vector<Foo> vecMove(std::move(vecAssign));
			Vector<Foo> vecMoveAssign;
			vecMoveAssign = std::move(vecMove);

			Foo e(50);
			Assert::AreEqual(*vec.Find(b), b);
			Assert::AreEqual(vec.Find(e), vec.end());

			Assert::ExpectException<std::runtime_error>([]() {Foo a(10); Vector<Foo> vecA; Vector<Foo> vecB; vecA.PushBack(a); vecB.PushBack(a); vecA.Remove(vecB.begin()); });
			Assert::ExpectException<std::runtime_error>([]() {Vector<Foo> vec; vec.Remove(vec.begin()); });
			Assert::ExpectException<std::runtime_error>([]() {Vector<Foo> vec; *vec.begin(); });
			Assert::ExpectException<std::runtime_error>([]() {Vector<Foo> vec; *vec.cbegin(); });

			vec.PushBack(c);
			vec.Remove(vec.Find(c));
			Assert::AreNotEqual(c, *--vec.end());

			Vector<Foo> vecFind;
			vecFind.PushBack(a);
			vecFind.PushBack(b);
			vecFind.PushBack(c);
			Assert::AreEqual(vecFind.Find(a), vecFind.begin());
			vecFind.Remove(vecFind.Find(a));
			Assert::AreEqual(*vecFind.begin(), b);
			Assert::AreEqual(*--vecFind.end(), c);
			Assert::AreEqual(vecFind.Size(), size_t(2));
			Assert::AreEqual(vecFind.Capacity(), size_t(4));
		}
		TEST_METHOD(Iterator)
		{
			Foo a(10);
			Foo b(20);
			Foo c(30);

			Vector<Foo> vec(3);
			vec.PushBack(a);
			vec.PushBack(b);
			vec.PushBack(c);

			Vector<Foo>::Iterator it;
			it = vec.begin();
			Assert::AreEqual(*it, a);
			++it;
			Assert::AreEqual(*it, b);
			it++;
			Assert::AreEqual(*it, c);
			Assert::AreEqual(it, --vec.end());
			--it;
			Assert::AreEqual(*it, b);
			it--;
			Assert::AreEqual(*it, a);

			Vector<Foo>::Iterator itCopy(it);
			Assert::IsTrue(it == itCopy);
			Assert::IsFalse(it != itCopy);

			Vector<Foo>::Iterator itConstructor(vec);
			Assert::IsTrue(it == itConstructor);
			Assert::IsFalse(it != itConstructor);


			Vector<Foo>::Iterator itConstructorIndex(vec, 1);
			Assert::IsTrue(it != itConstructorIndex);
			Assert::IsFalse(it == itConstructorIndex);
			--itConstructorIndex;
			Assert::IsTrue(it == itConstructorIndex);
			Assert::IsFalse(it != itConstructorIndex);
		}
		TEST_METHOD(ConstIterator)
		{
			Foo a(10);
			Foo b(20);
			Foo c(30);

			Vector<Foo> vec;
			vec.PushBack(a);
			vec.PushBack(b);
			vec.PushBack(c);

			Vector<Foo>::ConstIterator it;
			it = vec.cbegin();
			Assert::AreEqual(*it, a);
			++it;
			Assert::AreEqual(*it, b);
			it++;
			Assert::AreEqual(*it, c);
			Assert::AreEqual(it, --vec.cend());
			--it;
			Assert::AreEqual(*it, b);
			it--;
			Assert::AreEqual(*it, a);

			const Vector<Foo> vecConst = vec;
			Assert::AreEqual(vecConst.Front(), vec.Front());
			Assert::AreEqual(vecConst.Back(), vec.Back());
			Vector<Foo>::ConstIterator itConst;
			itConst = vecConst.begin();
			Assert::AreEqual(*itConst, a);
			++itConst;
			Assert::AreEqual(*itConst, b);
			itConst++;
			Assert::AreEqual(*itConst, c);
			Assert::AreEqual(itConst, --vecConst.end());
			--itConst;
			Assert::AreEqual(*itConst, b);
			itConst--;
			Assert::AreEqual(*itConst, a);

			Vector<Foo>::ConstIterator itCopy(it);
			Assert::IsTrue(it == itCopy);
			Assert::IsFalse(it != itCopy);

			Vector<Foo>::Iterator itNonConst = vec.begin();
			Vector<Foo>::ConstIterator itConstConversion(itNonConst);
			Assert::IsTrue(it == itConstConversion);
			Assert::IsFalse(it != itConstConversion);

			Vector<Foo>::ConstIterator itConstructor(vec);
			Assert::IsTrue(it == itConstructor);
			Assert::IsFalse(it != itConstructor);


			Vector<Foo>::ConstIterator itConstructorIndex(vec, 1);
			Assert::IsTrue(it != itConstructorIndex);
			Assert::IsFalse(it == itConstructorIndex);
			--itConstructorIndex;
			Assert::IsTrue(it == itConstructorIndex);
			Assert::IsFalse(it != itConstructorIndex);
		}



	private:
		_CrtMemState _startMemState;
	};
}
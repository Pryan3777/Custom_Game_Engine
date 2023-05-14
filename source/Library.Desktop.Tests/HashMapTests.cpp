#include "pch.h"
#include "CppUnitTest.h"
#include "HashMap.h"
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
	TEST_CLASS(HashMapTests)
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

		TEST_METHOD(ConstructorTest)
		{
			HashMap<const int, int> iiMap(size_t(3));
			HashMap<const int, Foo> ifMap(size_t(3));
			HashMap<const Foo, int> fiMap(size_t(3));
			HashMap<const Foo, Foo> ffMap(size_t(3));

			HashMap<const int, int> iiMapCopy(iiMap);
			HashMap<const int, int> iMapAssignment = iiMap;
			iMapAssignment = iiMap;
			HashMap<const int, int> iiMapMove(std::move(iiMapCopy));
			HashMap<const int, int> iMapMoveAssignment = iiMap;
			iMapMoveAssignment = std::move(iiMapMove);
		}
		TEST_METHOD(IteratorConstructorTest)
		{
			HashMap<const int, int> iiMap(size_t(3));
			HashMap<const int, int>::Iterator i;
			i = iiMap.begin();
			HashMap<const int, int>::Iterator it;
			it = i;
			HashMap<const int, int>::ConstIterator ci(i);
			ci = i;
			HashMap<const int, int>::ConstIterator ca = i;
			ca = ci;
		}
		TEST_METHOD(LargeBinTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(300));
			iiMap.Insert(std::pair(a, a));
			iiMap.Insert(std::pair(b, b));
			iiMap.Insert(std::pair(c, c));
			Assert::AreEqual(iiMap.Size(), size_t(2));

			HashMap<const int, int>::Iterator i = iiMap.begin();
			++i;
			i++;
			Assert::IsTrue(i == iiMap.end());

			HashMap<const int, int>::ConstIterator ic = iiMap.cbegin();
			++ic;
			ic++;
			Assert::IsTrue(ic == iiMap.cend());

			Assert::AreEqual(a, iiMap.Find(a)->first);
		}
		TEST_METHOD(InsertTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, a));
			iiMap.Insert(std::pair(b, b));
			iiMap.Insert(std::pair(c, c));
			Assert::AreEqual(iiMap.Size(), size_t(2));

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, x));
			ifMap.Insert(std::pair(b, y));
			ifMap.Insert(std::pair(c, z));
			Assert::AreEqual(ifMap.Size(), size_t(2));

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, a));
			fiMap.Insert(std::pair(y, b));
			fiMap.Insert(std::pair(z, c));
			Assert::AreEqual(fiMap.Size(), size_t(2));

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, x));
			ffMap.Insert(std::pair(y, y));
			ffMap.Insert(std::pair(z, z));
			Assert::AreEqual(ffMap.Size(), size_t(2));
		}
		TEST_METHOD(FindTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;
			int d = 30;

			Foo x(10);
			Foo y(20);
			Foo z(10);
			Foo w(30);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap.Find(a)->second);
			Assert::AreEqual(c, iiMap.Find(b)->second);
			Assert::AreEqual(b, iiMap.Find(c)->second);
			Assert::IsTrue(iiMap.end() == iiMap.Find(d));

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, y));
			ifMap.Insert(std::pair(b, z));
			ifMap.Insert(std::pair(c, x));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			Assert::AreEqual(y, ifMap.Find(a)->second);
			Assert::AreEqual(z, ifMap.Find(b)->second);
			Assert::AreEqual(y, ifMap.Find(c)->second);
			Assert::IsTrue(ifMap.end() == ifMap.Find(d));
			

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, b));
			fiMap.Insert(std::pair(y, c));
			fiMap.Insert(std::pair(z, a));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			Assert::AreEqual(b, fiMap.Find(x)->second);
			Assert::AreEqual(c, fiMap.Find(y)->second);
			Assert::AreEqual(b, fiMap.Find(z)->second);
			Assert::IsTrue(fiMap.end() == fiMap.Find(w));
			

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, y));
			ffMap.Insert(std::pair(y, z));
			ffMap.Insert(std::pair(z, x));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			Assert::AreEqual(y, ffMap.Find(x)->second);
			Assert::AreEqual(z, ffMap.Find(y)->second);
			Assert::AreEqual(y, ffMap.Find(z)->second);
			Assert::IsTrue(ffMap.end() == ffMap.Find(w));
		}
		TEST_METHOD(ConstFindTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;
			int d = 30;

			Foo x(10);
			Foo y(20);
			Foo z(10);
			Foo w(30);

			HashMap<const int, int> niiMap(size_t(3));
			niiMap.Insert(std::pair(a, b));
			niiMap.Insert(std::pair(b, c));
			niiMap.Insert(std::pair(c, a));
			const HashMap<const int, int> iiMap(niiMap);
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap.Find(a)->second);
			Assert::AreEqual(c, iiMap.Find(b)->second);
			Assert::AreEqual(b, iiMap.Find(c)->second);
			Assert::IsTrue(iiMap.end() == iiMap.Find(d));


			HashMap<const int, Foo> nifMap(size_t(3));
			nifMap.Insert(std::pair(a, y));
			nifMap.Insert(std::pair(b, z));
			nifMap.Insert(std::pair(c, x));
			const HashMap<const int, Foo> ifMap(nifMap);
			Assert::AreEqual(ifMap.Size(), size_t(2));
			Assert::AreEqual(y, ifMap.Find(a)->second);
			Assert::AreEqual(z, ifMap.Find(b)->second);
			Assert::AreEqual(y, ifMap.Find(c)->second);
			Assert::IsTrue(ifMap.end() == ifMap.Find(d));


			HashMap<const Foo, int> nfiMap(size_t(3));
			nfiMap.Insert(std::pair(x, b));
			nfiMap.Insert(std::pair(y, c));
			nfiMap.Insert(std::pair(z, a));
			HashMap<const Foo, int> fiMap(nfiMap);
			Assert::AreEqual(fiMap.Size(), size_t(2));
			Assert::AreEqual(b, fiMap.Find(x)->second);
			Assert::AreEqual(c, fiMap.Find(y)->second);
			Assert::AreEqual(b, fiMap.Find(z)->second);
			Assert::IsTrue(fiMap.end() == fiMap.Find(w));


			HashMap<const Foo, Foo> nffMap(size_t(3));
			nffMap.Insert(std::pair(x, y));
			nffMap.Insert(std::pair(y, z));
			nffMap.Insert(std::pair(z, x));
			HashMap<const Foo, Foo> ffMap(nffMap);
			Assert::AreEqual(ffMap.Size(), size_t(2));
			Assert::AreEqual(y, ffMap.Find(x)->second);
			Assert::AreEqual(z, ffMap.Find(y)->second);
			Assert::AreEqual(y, ffMap.Find(z)->second);
			Assert::IsTrue(ffMap.end() == ffMap.Find(w));
		}
		TEST_METHOD(IndexTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;
			int d = 30;

			Foo x(10);
			Foo y(20);
			Foo z(10);
			Foo w(30);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap[a]);
			Assert::AreEqual(c, iiMap[b]);
			Assert::AreEqual(b, iiMap[c]);
			iiMap[d] = d;
			Assert::AreEqual(iiMap.Size(), size_t(3));
			Assert::AreEqual(d, iiMap[d]);

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, y));
			ifMap.Insert(std::pair(b, z));
			ifMap.Insert(std::pair(c, x));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			Assert::AreEqual(y, ifMap[a]);
			Assert::AreEqual(z, ifMap[b]);
			Assert::AreEqual(y, ifMap[c]);
			ifMap[d] = w;
			Assert::AreEqual(ifMap.Size(), size_t(3));
			Assert::AreEqual(w, ifMap[d]);

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, b));
			fiMap.Insert(std::pair(y, c));
			fiMap.Insert(std::pair(z, a));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			Assert::AreEqual(b, fiMap[x]);
			Assert::AreEqual(c, fiMap[y]);
			Assert::AreEqual(b, fiMap[z]);
			fiMap[w] = d;
			Assert::AreEqual(fiMap.Size(), size_t(3));
			Assert::AreEqual(d, fiMap[w]);

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, y));
			ffMap.Insert(std::pair(y, z));
			ffMap.Insert(std::pair(z, x));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			Assert::AreEqual(y, ffMap[x]);
			Assert::AreEqual(z, ffMap[y]);
			Assert::AreEqual(y, ffMap[z]); 
			ffMap[w] = w;
			Assert::AreEqual(ffMap.Size(), size_t(3));
			Assert::AreEqual(d, fiMap[w]);
		}
		TEST_METHOD(RemoveTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, a));
			iiMap.Insert(std::pair(b, b));
			iiMap.Insert(std::pair(c, c));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			iiMap.Remove(a);
			Assert::AreEqual(iiMap.Size(), size_t(1));
			iiMap.Remove(b);
			Assert::AreEqual(iiMap.Size(), size_t(0));

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, x));
			ifMap.Insert(std::pair(b, y));
			ifMap.Insert(std::pair(c, z));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			ifMap.Remove(a);
			Assert::AreEqual(ifMap.Size(), size_t(1));
			ifMap.Remove(b);
			Assert::AreEqual(ifMap.Size(), size_t(0));

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, a));
			fiMap.Insert(std::pair(y, b));
			fiMap.Insert(std::pair(z, c));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			fiMap.Remove(x);
			Assert::AreEqual(fiMap.Size(), size_t(1));
			fiMap.Remove(y);
			Assert::AreEqual(fiMap.Size(), size_t(0));

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, x));
			ffMap.Insert(std::pair(y, y));
			ffMap.Insert(std::pair(z, z));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			ffMap.Remove(x);
			Assert::AreEqual(ffMap.Size(), size_t(1));
			ffMap.Remove(y);
			Assert::AreEqual(ffMap.Size(), size_t(0));
		}
		TEST_METHOD(ContainsKeyTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;
			int d = 30;

			Foo x(10);
			Foo y(20);
			Foo z(10);
			Foo w(30);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::IsTrue(iiMap.ContainsKey(a));
			Assert::IsTrue(iiMap.ContainsKey(b));
			Assert::IsTrue(iiMap.ContainsKey(c));
			Assert::IsFalse(iiMap.ContainsKey(d));
			
			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, y));
			ifMap.Insert(std::pair(b, z));
			ifMap.Insert(std::pair(c, x));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			Assert::IsTrue(ifMap.ContainsKey(a));
			Assert::IsTrue(ifMap.ContainsKey(b));
			Assert::IsTrue(ifMap.ContainsKey(c));
			Assert::IsFalse(ifMap.ContainsKey(d));
			
			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, b));
			fiMap.Insert(std::pair(y, c));
			fiMap.Insert(std::pair(z, a));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			Assert::IsTrue(fiMap.ContainsKey(x));
			Assert::IsTrue(fiMap.ContainsKey(y));
			Assert::IsTrue(fiMap.ContainsKey(z));
			Assert::IsFalse(fiMap.ContainsKey(w));
			
			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, y));
			ffMap.Insert(std::pair(y, z));
			ffMap.Insert(std::pair(z, x));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			Assert::IsTrue(ffMap.ContainsKey(x));
			Assert::IsTrue(ffMap.ContainsKey(y));
			Assert::IsTrue(ffMap.ContainsKey(z));
			Assert::IsFalse(ffMap.ContainsKey(w));
			
		}
		TEST_METHOD(ClearTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, a));
			iiMap.Insert(std::pair(b, b));
			iiMap.Insert(std::pair(c, c));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			iiMap.Clear();
			Assert::AreEqual(iiMap.Size(), size_t(0));

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, x));
			ifMap.Insert(std::pair(b, y));
			ifMap.Insert(std::pair(c, z));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			ifMap.Clear();
			Assert::AreEqual(ifMap.Size(), size_t(0));

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, a));
			fiMap.Insert(std::pair(y, b));
			fiMap.Insert(std::pair(z, c));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			fiMap.Clear();
			Assert::AreEqual(fiMap.Size(), size_t(0));

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, x));
			ffMap.Insert(std::pair(y, y));
			ffMap.Insert(std::pair(z, z));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			ffMap.Clear();
			Assert::AreEqual(ffMap.Size(), size_t(0));
		}
		TEST_METHOD(AtTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			Assert::ExpectException<std::runtime_error>([]() {HashMap<const int, int> iiMap(size_t(3)); iiMap.Insert(std::pair(10, 10)); iiMap.At(100); });

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap.At(a));
			Assert::AreEqual(c, iiMap.At(b));
			Assert::AreEqual(b, iiMap.At(c));

			HashMap<const int, Foo> ifMap(size_t(3));
			ifMap.Insert(std::pair(a, y));
			ifMap.Insert(std::pair(b, z));
			ifMap.Insert(std::pair(c, x));
			Assert::AreEqual(ifMap.Size(), size_t(2));
			Assert::AreEqual(y, ifMap.At(a));
			Assert::AreEqual(z, ifMap.At(b));
			Assert::AreEqual(y, ifMap.At(c));

			HashMap<const Foo, int> fiMap(size_t(3));
			fiMap.Insert(std::pair(x, b));
			fiMap.Insert(std::pair(y, c));
			fiMap.Insert(std::pair(z, a));
			Assert::AreEqual(fiMap.Size(), size_t(2));
			Assert::AreEqual(b, fiMap.At(x));
			Assert::AreEqual(c, fiMap.At(y));
			Assert::AreEqual(b, fiMap.At(z));

			HashMap<const Foo, Foo> ffMap(size_t(3));
			ffMap.Insert(std::pair(x, y));
			ffMap.Insert(std::pair(y, z));
			ffMap.Insert(std::pair(z, x));
			Assert::AreEqual(ffMap.Size(), size_t(2));
			Assert::AreEqual(y, ffMap.At(x));
			Assert::AreEqual(z, ffMap.At(y));
			Assert::AreEqual(y, ffMap.At(z));
		}
		TEST_METHOD(ConstAtTest)
		{
			const int a = 10;
			const int b = 20;
			const int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			const HashMap<const int, int> constiiMap = iiMap;
			Assert::AreEqual(constiiMap.Size(), size_t(2));
			Assert::AreEqual(b, constiiMap.At(a));
			Assert::AreEqual(c, constiiMap.At(b));
			Assert::AreEqual(b, constiiMap.At(c));
			Assert::ExpectException<std::runtime_error>([constiiMap]() {constiiMap.At(100); });
		}
		TEST_METHOD(BulkTest)
		{
			HashMap<const int, int> bulkMap(size_t(3));
			for (int i = 0; i < 1001; ++i)
			{
				bulkMap.Insert(std::pair<const int, int>(i, i));
			}
			bulkMap.Remove(1001);
			for (int i = 0; i < 1000; ++i)
			{
				const int f = i;
				Assert::AreEqual(i, bulkMap.At(f));
				Assert::AreEqual(i, bulkMap[f]);
				Assert::IsTrue(bulkMap.ContainsKey(i));
			}
			Assert::IsFalse(bulkMap.ContainsKey(1001));
			HashMap<const int, int>::Iterator i;
			i = bulkMap.begin();
			while (i != bulkMap.end())
			{
				i++;
			}
			i = bulkMap.begin();
			while (i != bulkMap.end())
			{
				++i;
			}
			HashMap<const int, int> bulkMapCopy(size_t(3));
			bulkMapCopy = bulkMap;
			Assert::AreEqual(bulkMapCopy.Size(), bulkMap.Size());
		}
		TEST_METHOD(ConstBulkTest)
		{
			HashMap<const int, int> bulkMap(size_t(3));
			for (int i = 0; i < 1001; ++i)
			{
				bulkMap.Insert(std::pair<const int, int>(i, i));
			}
			bulkMap.Remove(1001);
			const HashMap<const int, int> bulkConstMap = bulkMap;
			for (int i = 0; i < 1000; ++i)
			{
				const int f = i;
				Assert::AreEqual(i, bulkConstMap.At(f));
				Assert::IsTrue(bulkConstMap.ContainsKey(i));
			}
			Assert::IsFalse(bulkConstMap.ContainsKey(1001));
			HashMap<const int, int>::ConstIterator i;
			i = bulkMap.cbegin();
			while (i != bulkMap.cend())
			{
				i++;
			}
			i = bulkMap.cbegin();
			while (i != bulkMap.cend())
			{
				++i;
			}
		}
		TEST_METHOD(IteratorTest)
		{
			int a = 10;
			int b = 20;
			int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap.At(a));
			Assert::AreEqual(c, iiMap.At(b));
			Assert::AreEqual(b, iiMap.At(c));

			HashMap<const int, int>::Iterator i = iiMap.begin();
			Assert::IsTrue((*i).second == b);
			i->second;
			Assert::IsTrue(i->first == a);
			i++;
			Assert::IsTrue((*i).second == a);
			++i;
			Assert::IsTrue(i == iiMap.end());
			Assert::IsTrue(i != iiMap.begin());

			Assert::ExpectException<std::runtime_error>([]() {HashMap<const int, int> iiMap(size_t(3)); HashMap<const int, int>::Iterator i = iiMap.end(); *i; });
			Assert::ExpectException<std::runtime_error>([]() {HashMap<const int, int> iiMap(size_t(3)); HashMap<const int, int>::Iterator i = iiMap.end(); i->first; });
		}
		TEST_METHOD(ConstIteratorTest)
		{
			const int a = 10;
			const int b = 20;
			const int c = 10;

			Foo x(10);
			Foo y(20);
			Foo z(10);

			HashMap<const int, int> iiMap(size_t(3));
			iiMap.Insert(std::pair(a, b));
			iiMap.Insert(std::pair(b, c));
			iiMap.Insert(std::pair(c, a));
			Assert::AreEqual(iiMap.Size(), size_t(2));
			Assert::AreEqual(b, iiMap.At(a));
			Assert::AreEqual(c, iiMap.At(b));
			Assert::AreEqual(b, iiMap.At(c));

			const HashMap<const int, int> constMap = iiMap;
			HashMap<const int, int>::ConstIterator i = constMap.begin();
			Assert::IsTrue(i == constMap.cbegin());
			Assert::IsTrue((*i).second == b);
			i++;
			Assert::IsTrue(i->second == a);
			++i;
			Assert::IsTrue(i == constMap.end());
			Assert::IsTrue(i == constMap.cend());
			Assert::IsTrue(i != constMap.cbegin());

			Assert::ExpectException<std::runtime_error>([]() {HashMap<const int, int> iiMap(size_t(3)); HashMap<const int, int>::ConstIterator i = iiMap.cend(); *i; });
			Assert::ExpectException<std::runtime_error>([]() {HashMap<const int, int> iiMap(size_t(3)); HashMap<const int, int>::ConstIterator i = iiMap.cend(); i->first; });
		}

	private:
		_CrtMemState _startMemState;
	};
}
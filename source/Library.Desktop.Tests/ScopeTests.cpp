#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ScopeTests)
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

		TEST_METHOD(Paul)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			Scope movedScope = std::move(scope);
#pragma warning(push)
#pragma warning(disable:26800)
			Assert::IsTrue(scope.IsEmpty());
#pragma warning(pop)
			Assert::AreEqual(size_t(3), movedScope.Size());
			Datum* foundDatum = movedScope.Find(a);
			Assert::IsTrue(&aDatum == foundDatum);

			foundDatum = movedScope.Find(b);
			Assert::IsTrue(&bDatum == foundDatum);

			foundDatum = movedScope.Find(c);
			Assert::IsTrue(cDatum == foundDatum);
			Assert::IsTrue(foundDatum->GetScope()->GetParent() == &movedScope);

			Scope reparentedScope{ std::move(cScope) };
			Assert::IsNull(reparentedScope.GetParent());
		}

		TEST_METHOD(ConstructorTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);
		}

		TEST_METHOD(CopyConstructorTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope s(scope);
			Assert::IsTrue(s.Size() == size_t(3));
			Assert::IsTrue(s[a] == x);
			Assert::IsTrue(s[b] == y);
		}

		TEST_METHOD(AssignmentOperatorTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope s;
			s = scope;
			Assert::IsTrue(s.Size() == size_t(3));
			Assert::IsTrue(s[a] == x);
			Assert::IsTrue(s[b] == y);
		}

		TEST_METHOD(MoveConstructorTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope s(std::move(scope));
			Assert::IsTrue(s.Size() == size_t(3));
			Assert::IsTrue(s[a] == x);
			Assert::IsTrue(s[b] == y);
		}

		TEST_METHOD(MoveAssignmentOperatorTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope s;
			s = std::move(scope);
			Assert::IsTrue(s.Size() == size_t(3));
			Assert::IsTrue(s[a] == x);
			Assert::IsTrue(s[b] == y);
		}
		TEST_METHOD(SearchTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;
			const string d = "D"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope& dScope = cScope.AppendScope(d);
			Assert::IsTrue(*dScope.Search(a) == aDatum);
		}
		TEST_METHOD(OrphanAdoptTest)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope scopeNew;
			Scope& u = (*scope.Find("C"s))[0];
			scopeNew.Adopt(u, "C"s);
		}
		TEST_METHOD(Equivalence)
		{
			Scope scope;
			const string a = "A"s;
			const string b = "B"s;
			const string c = "C"s;

			float x(10);
			float y(20);
			//float z(30);

			Datum& aDatum = scope.Append(a);
			aDatum = "Hello, World!"s;
			Datum& bDatum = scope.Append(b);
			bDatum = glm::mat4(5);
			Scope& cScope = scope.AppendScope(c);
			Assert::AreEqual(size_t(3), scope.Size());

			Assert::AreEqual(size_t(0), cScope.Size());
			auto [cDatum, datumindex] = scope.FindContainedScope(cScope);
			Assert::IsNotNull(cDatum);

			aDatum = x;
			bDatum = y;

			Assert::IsTrue(scope[a] == x);
			Assert::IsTrue(scope[b] == y);

			Scope s(scope);
			Assert::IsTrue(s == scope);
			Assert::IsFalse(s != scope);

			scope.Find("C"s)->GetScope()->AppendScope("z"s);
			s.Find("C"s)->GetScope()->AppendScope("z"s);
			Assert::IsTrue(scope == s);
		}


		TEST_METHOD(OtherTests)
		{
			{
				Scope s;
				Assert::IsTrue(s.Search("Hi"s) == nullptr);
			}
			{
				Scope s;
				Datum &aDatum = s.Append("A"s);
				Assert::IsTrue(s[0] == aDatum);
			}
			{
				Scope a;
				Scope b;
				Datum &aDatum = a.Append("A");
				Datum &bDatum = b.Append("A");
				aDatum = 10;
				bDatum = 10;
				Assert::IsTrue(a == b);
				bDatum = 20;
				Assert::IsTrue(a != b);
			}
			{
				Scope s;
				Scope a;
				Assert::IsTrue(s.FindContainedScope(a).first == nullptr);
			}
			{
				Scope *s = new Scope();
				Scope *t = new Scope();
				s->Append("a");
				t->Append("b");
				Assert::IsFalse(s->Equals(t));
				delete(s);
				delete(t);
			}
			{
				Scope s;
				s.AppendScope("A"s);
				Scope* t = std::move(s["A"].GetScope());
				delete(t);
			}
			{
				Scope** out = new Scope*;
				Scope s;
				s.Append("A");
				s.Search("A", out);
				Assert::IsTrue(*out == &s);
				delete(out);
			}
		}
		
		

	private:
		_CrtMemState _startMemState;
	};
}
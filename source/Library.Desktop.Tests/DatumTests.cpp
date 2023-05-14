#pragma once

#include "pch.h"
#include "CppUnitTest.h"

#include <cstddef>
#include <string>
#include <glm/glm.hpp>

#include "Datum.h"
#include "Foo.h"
#include "RTTI.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
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
	TEST_CLASS(DatumTests)
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

		
		TEST_METHOD(IntConstructors)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(IntConstructorsExternal)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				int data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::AreEqual(d.Size(), size_t(3));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);
			}
		}
		TEST_METHOD(IntConst)
		{			
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));

				const Datum e = d;
				Assert::IsTrue(a == e.GetInt());
				Assert::IsTrue(b == e.GetInt(1));
				Assert::IsTrue(c == e.GetInt(2));
				Assert::IsTrue(a == e.FrontInt());
				Assert::IsTrue(c == e.BackInt());
				Assert::AreEqual(size_t(0), e.Find(a));
				Assert::AreEqual(size_t(1), e.Find(b));
				Assert::AreEqual(size_t(2), e.Find(c));
			}
		}
		TEST_METHOD(IntSet)
		{			
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));
			}
		}
		TEST_METHOD(IntPushBack)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));
			}
		}
		TEST_METHOD(IntRemove)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));
				d.RemoveAt(1);
				Assert::AreEqual(a, d.GetInt(0));
				Assert::AreEqual(c, d.GetInt(1));
				d.Remove(a);
				Assert::AreEqual(c, d.GetInt(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(IntResize)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));
				d.Resize(2);
				Assert::AreEqual(a, d.GetInt(0));
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(IntFrontBack)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.FrontInt());
				Assert::AreEqual(c, d.BackInt());
			}
		}
		TEST_METHOD(IntDatumCompare)
		{
			{
				int a = 0;
				int b = 1;
				//int c = 2;

				Datum d;
				d.SetType(Datum::DatumTypes::Integer);
				d.Resize(3);
				d.Set(a, 2);
				Datum e;
				e.SetType(Datum::DatumTypes::Integer);
				e.Resize(3);
				e.Set(a, 2);
				Assert::IsTrue(d == e); 

				d.Set(b, 0);
				Assert::IsTrue(d != e);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}
		}
		TEST_METHOD(IntDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::Integer);
			d.Resize(3);
			Assert::AreEqual(d.GetInt(0), 0);
			Assert::AreEqual(d.GetInt(1), 0);
			Assert::AreEqual(d.GetInt(2), 0);
		}
		TEST_METHOD(IntFind)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Integer);
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));
			}
		}
		TEST_METHOD(IntExternal)
		{
			{
				int a = 0;
				int b = 1;
				int c = 2;

				int data[3]{a, b, c};

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::AreEqual(a, d.GetInt());
				Assert::AreEqual(b, d.GetInt(1));
				Assert::AreEqual(c, d.GetInt(2));
				Assert::AreEqual(a, d.FrontInt());
				Assert::AreEqual(c, d.BackInt());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3);	 d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3); int in = 0; d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3); int in = 0; d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; int data[3]{ 0, 1, 2 }; d.SetStorage(data, 3); int in = 0; d.PushBack(in); });
			}
		}




		TEST_METHOD(FloatConstructors)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(FloatConst)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));

				const Datum e = d;
				Assert::IsTrue(a == e.GetFloat());
				Assert::IsTrue(b == e.GetFloat(1));
				Assert::IsTrue(c == e.GetFloat(2));
				Assert::IsTrue(a == e.FrontFloat());
				Assert::IsTrue(c == e.BackFloat());
				Assert::AreEqual(size_t(0), e.Find(a));
				Assert::AreEqual(size_t(1), e.Find(b));
				Assert::AreEqual(size_t(2), e.Find(c));
			}
		}
		TEST_METHOD(FloatSet)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));
			}
		}
		TEST_METHOD(FloatPushBack)
		{
			{
				float a = 0.0f;
				float b = 1.0f;
				float c = 2.0f;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));
			}
		}
		TEST_METHOD(FloatRemove)
		{
			{
				float a = 0.0f;
				float b = 1.0f;
				float c = 2.0f;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));
				d.RemoveAt(1);
				Assert::AreEqual(a, d.GetFloat(0));
				Assert::AreEqual(c, d.GetFloat(1));
				d.Remove(a);
				Assert::AreEqual(c, d.GetFloat(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(FloatResize)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));
				d.Resize(2);
				Assert::AreEqual(a, d.GetFloat(0));
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(FloatFrontBack)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.FrontFloat());
				Assert::AreEqual(c, d.BackFloat());
			}
		}
		TEST_METHOD(FloatDatumCompare)
		{
			{
				float a = 0;
				float b = 1;
				//float c = 2;

				Datum d;
				d.SetType(Datum::DatumTypes::Float);
				d.Resize(3);
				d.Set(a, 2);
				Datum e;
				e.SetType(Datum::DatumTypes::Float);
				e.Resize(3);
				e.Set(a, 2);
				Assert::IsTrue(d == e);


				d.Set(b, 0);
				Assert::IsTrue(d != e);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}
		}
		TEST_METHOD(FloatDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::Float);
			d.Resize(3);
			Assert::AreEqual(d.GetFloat(0), 0.0f);
			Assert::AreEqual(d.GetFloat(1), 0.0f);
			Assert::AreEqual(d.GetFloat(2), 0.0f);
		}
		TEST_METHOD(FloatFind)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Float);
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));
			}
		}
		TEST_METHOD(FloatExternal)
		{
			{
				float a = 0;
				float b = 1;
				float c = 2;

				float data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::AreEqual(a, d.GetFloat());
				Assert::AreEqual(b, d.GetFloat(1));
				Assert::AreEqual(c, d.GetFloat(2));
				Assert::AreEqual(a, d.FrontFloat());
				Assert::AreEqual(c, d.BackFloat());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3);	 d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3); float in = 0.0f; d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3); float in = 0.0f; d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; float data[3]{ 0.0f, 1.0f, 2.0f }; d.SetStorage(data, 3); float in = 0.0f; d.PushBack(in); });
			}
		}





		TEST_METHOD(VectorConstructors)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(VectorConst)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);

				const Datum e = d;
				Assert::IsTrue(a == e.GetVec());
				Assert::IsTrue(b == e.GetVec(1));
				Assert::IsTrue(c == e.GetVec(2));
				Assert::IsTrue(a == e.FrontVec());
				Assert::IsTrue(c == e.BackVec());
				Assert::AreEqual(size_t(0), e.Find(a));
				Assert::AreEqual(size_t(1), e.Find(b));
				Assert::AreEqual(size_t(2), e.Find(c));
			}
		}
		TEST_METHOD(VectorSet)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);
			}
		}
		TEST_METHOD(VectorPushBack)
		{
			{
				Datum d;

				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				d.SetType(Datum::DatumTypes::Vector);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);
			}
		}
		TEST_METHOD(VectorRemove)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);
				d.RemoveAt(1);
				Assert::AreEqual(a.x, d.GetVec(0).x);
				Assert::AreEqual(c.x, d.GetVec(1).x);
				d.Remove(a);
				Assert::IsTrue(c == d.GetVec(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(VectorResize)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);
				d.Resize(2);
				Assert::AreEqual(a.x, d.GetVec(0).x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(VectorFrontBack)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.FrontVec().x);
				Assert::AreEqual(c.x, d.BackVec().x);
			}
		}
		TEST_METHOD(VectorDatumCompare)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				//glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.SetType(Datum::DatumTypes::Vector);
				d.Resize(3);
				d.Set(a, 2);
				Datum e;
				e.SetType(Datum::DatumTypes::Vector);
				e.Resize(3);
				e.Set(a, 2);
				Assert::IsTrue(d == e);

				d.Set(b, 0);
				Assert::IsTrue(d != e);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}
		}
		TEST_METHOD(VectorDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::Vector);
			d.Resize(3);
			Assert::IsTrue(d.GetVec(0) == d.GetVec(1));
			Assert::IsTrue(d.GetVec(0) == d.GetVec(2));
		}
		TEST_METHOD(VectorFind)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Vector);
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::AreEqual(a.x, d.GetVec().x);
				Assert::AreEqual(b.x, d.GetVec(1).x);
				Assert::AreEqual(c.x, d.GetVec(2).x);

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));
			}
		}
		TEST_METHOD(VectorExternal)
		{
			{
				glm::vec4 a = glm::vec4(0, 0, 0, 0);
				glm::vec4 b = glm::vec4(1, 1, 1, 1);
				glm::vec4 c = glm::vec4(2, 2, 2, 2);

				glm::vec4 data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetVec());
				Assert::IsTrue(b == d.GetVec(1));
				Assert::IsTrue(c == d.GetVec(2));
				Assert::IsTrue(a == d.FrontVec());
				Assert::IsTrue(c == d.BackVec());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3);	 d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3); glm::vec4 in = glm::vec4(0,0,0,0); d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3); glm::vec4 in = glm::vec4(0,0,0,0); d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 data[3]{ glm::vec4(0,0,0,0), glm::vec4(1,1,1,1), glm::vec4(2,2,2,2) }; d.SetStorage(data, 3); glm::vec4 in = glm::vec4(0,0,0,0); d.PushBack(in); });
			}
		}





		TEST_METHOD(MatrixConstructors)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(MatrixConst)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));

				const Datum e = d;
				Assert::IsTrue(a == e.GetMat());
				Assert::IsTrue(b == e.GetMat(1));
				Assert::IsTrue(c == e.GetMat(2));
				Assert::IsTrue(a == e.FrontMat());
				Assert::IsTrue(c == e.BackMat());
				Assert::AreEqual(size_t(0), e.Find(a));
				Assert::AreEqual(size_t(1), e.Find(b));
				Assert::AreEqual(size_t(2), e.Find(c));
			}
		}
		TEST_METHOD(MatrixSet)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));
			}
		}
		TEST_METHOD(MatrixPushBack)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));
			}
		}
		TEST_METHOD(MatrixRemove)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));
				d.RemoveAt(1);
				Assert::IsTrue(a == d.GetMat(0));
				Assert::IsTrue(c == d.GetMat(1));
				d.Remove(a);
				Assert::IsTrue(c == d.GetMat(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(MatrixResize)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));
				d.Resize(2);
				Assert::IsTrue(a == d.GetMat(0));
				Assert::IsTrue(b == d.GetMat(1));
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(MatrixFrontBack)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.FrontMat());
				Assert::IsTrue(c == d.BackMat());
			}
		}
		TEST_METHOD(MatrixDatumCompare)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				//glm::mat4 c = glm::mat4(2);

				Datum d;
				d.SetType(Datum::DatumTypes::Matrix);
				d.Resize(3);
				d.Set(a, 2);
				Datum e;
				e.SetType(Datum::DatumTypes::Matrix);
				e.Resize(3);
				e.Set(a, 2);
				Assert::IsTrue(d == e);

				d.Set(b, 0);
				Assert::IsTrue(d != e);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}
		}
		TEST_METHOD(MatrixDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::Matrix);
			d.Resize(3);
			Assert::IsTrue(d.GetMat(0) == d.GetMat(1));
			Assert::IsTrue(d.GetMat(0) == d.GetMat(2));
		}
		TEST_METHOD(MatrixFind)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Matrix);
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));
			}
		}
		TEST_METHOD(MatrixExternal)
		{
			{
				glm::mat4 a = glm::mat4(0);
				glm::mat4 b = glm::mat4(1);
				glm::mat4 c = glm::mat4(2);

				glm::mat4 data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetMat());
				Assert::IsTrue(b == d.GetMat(1));
				Assert::IsTrue(c == d.GetMat(2));
				Assert::IsTrue(a == d.FrontMat());
				Assert::IsTrue(c == d.BackMat());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3);	 d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3); glm::mat4 in = glm::mat4(0); d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3); glm::mat4 in = glm::mat4(0); d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 data[3]{ glm::mat4(0), glm::mat4(1), glm::mat4(2) }; d.SetStorage(data, 3); glm::mat4 in = glm::mat4(0); d.PushBack(in); });
			}
		}




		TEST_METHOD(StringConstructors)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(StringConst)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));

				const Datum e = d;
				Assert::IsTrue(a == e.GetString());
				Assert::IsTrue(b == e.GetString(1));
				Assert::IsTrue(c == e.GetString(2));
				Assert::IsTrue(a == e.FrontString());
				Assert::IsTrue(c == e.BackString());
				Assert::AreEqual(size_t(0), e.Find(a));
				Assert::AreEqual(size_t(1), e.Find(b));
				Assert::AreEqual(size_t(2), e.Find(c));
			}
		}
		TEST_METHOD(StringSet)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));
			}
		}
		TEST_METHOD(StringPushBack)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));
			}
		}
		TEST_METHOD(StringRemove)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));
				d.RemoveAt(1);
				Assert::IsTrue(a == d.GetString(0));
				Assert::AreEqual(c, d.GetString(1));
				Assert::IsTrue(c == d.GetString(1));
				d.Remove(a);
				Assert::AreEqual(c, d.GetString(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(StringResize)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));
				d.Resize(2);
				Assert::IsTrue(a == d.GetString(0));
				Assert::IsTrue(b == d.GetString(1));
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(StringFrontBack)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.FrontString());
				Assert::IsTrue(c == d.BackString());
			}
		}
		TEST_METHOD(StringDatumCompare)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				//std::string c = std::string("c");

				Datum d;
				d.SetType(Datum::DatumTypes::String);
				d.Resize(3);
				d.Set(a, 2);
				Datum e;
				e.SetType(Datum::DatumTypes::String);
				e.Resize(3);
				e.Set(a, 2);
				Assert::IsTrue(d == e);

				d.Set(b, 0);
				Assert::IsTrue(d != e);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}

			{
				Datum d;
				d.SetType(Datum::DatumTypes::String);
				d.Resize(1);
				Datum e(d);
				d.PushBack(std::string("a"));
				e.PushBack(std::string("b"));
				Assert::IsTrue(d != e);
			}
		}
		TEST_METHOD(StringDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::String);
			d.Resize(3);
			Assert::IsTrue(d.GetString(0) == d.GetString(1));
			Assert::IsTrue(d.GetString(0) == d.GetString(2));
		}
		TEST_METHOD(StringFind)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::String);
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));
			}
		}
		TEST_METHOD(StringExternal)
		{
			{
				std::string a = std::string("a");
				std::string b = std::string("b");
				std::string c = std::string("c");

				std::string data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, 3);
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetString());
				Assert::IsTrue(b == d.GetString(1));
				Assert::IsTrue(c == d.GetString(2));
				Assert::IsTrue(a == d.FrontString());
				Assert::IsTrue(c == d.BackString());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3);	 d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3); std::string in = std::string("a"); d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3); std::string in = std::string("a"); d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string data[3]{ std::string("a"), std::string("b"), std::string("c") }; d.SetStorage(data, 3); std::string in = std::string("a"); d.PushBack(in); });
			}
		}




		TEST_METHOD(PointerConstructors)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));

				Datum dCopy(d);
				Assert::IsTrue(d == dCopy);

				Datum dAssign;
				dAssign = dCopy;
				Assert::IsTrue(d == dAssign);

				Datum dMove(std::move(dCopy));
				Assert::IsTrue(d == dMove);

				Datum dMoveAssign;
				dMoveAssign = std::move(dAssign);
				Assert::IsTrue(d == dMoveAssign);

				Datum dSet;
				dSet = a;
			}
		}
		TEST_METHOD(PointerConst)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));

				const Datum h = d;
				Assert::IsTrue(a == h.GetRTTI());
				Assert::IsTrue(b == h.GetRTTI(1));
				Assert::IsTrue(c == h.GetRTTI(2));
				Assert::IsTrue(a == h.FrontRTTI());
				Assert::IsTrue(c == h.BackRTTI());
				Assert::AreEqual(size_t(0), h.Find(a));
				Assert::AreEqual(size_t(1), h.Find(b));
				Assert::AreEqual(size_t(2), h.Find(c));
			}
		}
		TEST_METHOD(PointerSet)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));


			}
		}
		TEST_METHOD(PointerPushBack)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				d.PushBack(a);
				d.PushBack(b);
				d.PushBack(c);
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));
			}
		}
		TEST_METHOD(PointerRemove)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));
				d.RemoveAt(1);
				Assert::IsTrue(a == d.GetRTTI(0));
				Assert::IsTrue(c == d.GetRTTI(1));
				d.Remove(a);
				Assert::IsTrue(c == d.GetRTTI(0));
				Assert::IsTrue(!d.Remove(a));
			}
		}
		TEST_METHOD(PointerResize)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));
				d.Resize(2);
				Assert::IsTrue(a == d.GetRTTI(0));
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::AreEqual(size_t(2), d.Size());
			}
		}
		TEST_METHOD(PointerFrontBack)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.FrontRTTI());
				Assert::IsTrue(c == d.BackRTTI());
			}
		}
		TEST_METHOD(PointerDatumCompare)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;

				Datum d;
				d.SetType(Datum::DatumTypes::Pointer);
				d.Resize(3);
				d.Set(a, 2);
				Datum h;
				h.SetType(Datum::DatumTypes::Pointer);
				h.Resize(3);
				h.Set(a, 2);
				Assert::IsTrue(d == h);

				d.Set(b, 0);
				Assert::IsTrue(d != h);
				Assert::IsTrue(d == b);
				Assert::IsTrue(d != a);
			}

			{
				UnitTests::Foo x(10);
				UnitTests::Foo y(20);

				UnitTests::Foo* a = &x;
				UnitTests::Foo* b = &y;

				Datum d;
				d.SetType(Datum::DatumTypes::Pointer);
				Datum e(d);

				RTTI* z = nullptr;
				d.PushBack(z);
				e.PushBack(z);
				Assert::IsTrue(d == e);

				d.Set(a);
				Assert::IsTrue(d != e);

				e.Set(b);
				Assert::IsTrue(d != e);

				e.Set(a);
				Assert::IsTrue(d == e);
			}
		}
		TEST_METHOD(PointerDefaultValues)
		{
			Datum d;
			d.SetType(Datum::DatumTypes::Pointer);
			d.Resize(3);
			Assert::IsTrue(d.GetRTTI(0) == d.GetRTTI(1));
			Assert::IsTrue(d.GetRTTI(0) == d.GetRTTI(2));
		}
		TEST_METHOD(PointerFind)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				UnitTests::Foo* a = &e;
				UnitTests::Foo* b = &f;
				UnitTests::Foo* c = &g;

				Datum d;
				d.Size();
				d.SetType(Datum::DatumTypes::Pointer);
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				d.Resize(size_t(3));
				Assert::AreEqual(d.Size(), size_t(3));
				d.Set(a);
				d.Set(b, size_t(1));
				d.Set(c, size_t(2));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));

				Assert::AreEqual(size_t(0), d.Find(a));
				Assert::AreEqual(size_t(1), d.Find(b));
				Assert::AreEqual(size_t(2), d.Find(c));


			}
		}
		TEST_METHOD(PointerExternal)
		{
			{
				UnitTests::Foo e(10);
				UnitTests::Foo f(20);
				UnitTests::Foo g(30);

				RTTI* a = &e;
				RTTI* b = &f;
				RTTI* c = &g;

				RTTI* data[3]{ a, b, c };

				Datum d;
				d.Size();
				d.SetStorage(data, size_t(3));
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				Assert::AreEqual(d.Size(), size_t(3));
				Assert::IsTrue(a == d.GetRTTI());
				Assert::IsTrue(b == d.GetRTTI(1));
				Assert::IsTrue(c == d.GetRTTI(2));
				Assert::IsTrue(a == d.FrontRTTI());
				Assert::IsTrue(c == d.BackRTTI());

				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); d.PopBack(); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); d.RemoveAt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); d.Resize(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); UnitTests::Foo ina(0); RTTI* in = &ina; d.Remove(in); });
				//Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); UnitTests::Foo ina(0); RTTI* in = &ina; d.Set(in); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo e(10); UnitTests::Foo f(20); UnitTests::Foo g(30); RTTI* data[3]{ &e, &f, &g }; d.SetStorage(data, 3); UnitTests::Foo ina(0); RTTI* in = &ina; d.PushBack(in); });
			}
		}


		TEST_METHOD(Exceptions)
		{
			{
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.Resize(1); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.RemoveAt(0); });

				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Integer); int b = 10;  int* a = &b;  d.SetStorage(a, 3); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Float  ); float b = 10.0f; float* a = &b;  d.SetStorage(a, 3); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Vector ); glm::vec4 b = glm::vec4(0, 0, 0, 0);  glm::vec4* a = &b;  d.SetStorage(a, 3); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Matrix ); glm::mat4 b = glm::mat4(0); glm::mat4* a = &b;  d.SetStorage(a, 3); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::String ); std::string b("b");  std::string* a = &b;  d.SetStorage(a, 3); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Pointer); UnitTests::Foo c(10); RTTI* b = &c; RTTI** a = &b;  d.SetStorage(a, 3); });
			
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Integer); int b = 10; d.Set(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Float  ); float b = 10.0f;  d.Set(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Vector ); glm::vec4 b = glm::vec4(0, 0, 0, 0);  d.Set(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Matrix ); glm::mat4 b = glm::mat4(0);   d.Set(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::String ); std::string b("b");   d.Set(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Pointer); UnitTests::Foo c(10); RTTI* b = &c;   d.Set(b); });

				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Integer); d.GetInt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Float  ); d.GetFloat(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Vector ); d.GetVec(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Matrix ); d.GetMat(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::String ); d.GetString(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Pointer); d.GetRTTI(0); });

				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Integer); const Datum e(d); e.GetInt(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Float  ); const Datum e(d); e.GetFloat(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Vector ); const Datum e(d); e.GetVec(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Matrix ); const Datum e(d); e.GetMat(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::String ); const Datum e(d); e.GetString(0); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; d.SetType(Datum::DatumTypes::Pointer); const Datum e(d); e.GetRTTI(0); });

				Assert::ExpectException<std::runtime_error>([]() {Datum d; int b = 10; d.PushBack(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; float b = 10.0f;  d.PushBack(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::vec4 b = glm::vec4(0, 0, 0, 0);  d.PushBack(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; glm::mat4 b = glm::mat4(0);   d.PushBack(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; std::string b("b");   d.PushBack(b); });
				Assert::ExpectException<std::runtime_error>([]() {Datum d; UnitTests::Foo c(10); RTTI* b = &c;   d.PushBack(b); });
			
				Datum d;
				d.SetType(Datum::DatumTypes::Integer);
				d.PushBack(0);
				d.RemoveAt(0);
				Assert::IsTrue(d.Size() == 0);
			}
		}
		TEST_METHOD(Scope)
		{
			{
				FieaGameEngine::Scope s;
				FieaGameEngine::Scope* sp = new FieaGameEngine::Scope();
				Datum d;
				d = sp;
				delete(sp);
			}
			{
				FieaGameEngine::Scope s;
				FieaGameEngine::Scope & aScope = s.AppendScope("A"s);
				FieaGameEngine::Scope t;
				FieaGameEngine::Scope & bScope = t.AppendScope("B"s);
				Assert::IsTrue(s != t);
				aScope;
				bScope;
			}
			{
				FieaGameEngine::Scope s;
				FieaGameEngine::Scope& aScope = s.AppendScope("A"s);
				FieaGameEngine::Scope& bScope = s.AppendScope("A"s);
				Datum* d = s.Find("A"s);
				Assert::IsTrue(*d->GetScope(0) == aScope);
				Assert::IsTrue(*d->GetScope(1) == bScope);
				Assert::IsTrue(*d->FrontScope() == aScope);
				Assert::IsTrue(*d->BackScope() == bScope);
			}
			{
				FieaGameEngine::Scope r;
				r.AppendScope("A"s);
				r.AppendScope("A"s);
				const FieaGameEngine::Scope s = r;
				const Datum *d = s.Find("A"s);
				Assert::IsTrue(d->GetScope(0) == d->FrontScope());
				Assert::IsTrue(d->GetScope(1) == d->BackScope());
			}
			{
				FieaGameEngine::Scope s;
				FieaGameEngine::Scope * a = &s.AppendScope("A");
				Assert::IsTrue(s["A"].Find(a) == 0);
			}
			{
				FieaGameEngine::Scope r;
				&r.AppendScope("A");
				const FieaGameEngine::Scope s(r);
				const FieaGameEngine::Scope* a = s.Find("A")->GetScope(0);
				Assert::IsTrue(s.Find("A")->Find(a) == 0);
			}
			{
				FieaGameEngine::Scope s;
				FieaGameEngine::Scope t;
				FieaGameEngine::Datum& aDatum = s.Append("A"s);
				FieaGameEngine::Datum& bDatum = t.Append("A"s);
				aDatum = 10;
				bDatum = 20;
				Assert::IsTrue(s != t);
			}
			{
				Datum a;
				Datum b;
				a.SetType(Datum::DatumTypes::Table);
				b.SetType(Datum::DatumTypes::Table);
				a.Resize(1);
				b.Resize(1);
				FieaGameEngine::Scope* s = new FieaGameEngine::Scope();
				FieaGameEngine::Scope* t = new FieaGameEngine::Scope();
				t->Append("A");
				a.Set(s);
				b.Set(t);
				Assert::IsTrue(a != b);
				delete(s);
				delete(t);
			}
			{
				Datum a;
				Datum b;
				a.SetType(Datum::DatumTypes::Table);
				b.SetType(Datum::DatumTypes::Table);
				a.Resize(1);
				b.Resize(1);
				FieaGameEngine::Scope* s = new FieaGameEngine::Scope();
				FieaGameEngine::Scope* t = nullptr;
				a.Set(s);
				b.Set(t);
				Assert::IsTrue(a != b);
				delete(s);
			}
			{
				Assert::ExpectException<std::runtime_error>([]() {Datum a; a.GetScope(); });
			}
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Table);
				a.Resize(1);
				const Datum c = a;
				Assert::IsTrue(c.GetScope() == nullptr);
				Assert::ExpectException<std::runtime_error>([a]() {a.GetScope(1); });
			}
			{
				Datum d;
				RTTI* p = nullptr;
				Assert::IsFalse(d == p);
			}
		}

	private:
		_CrtMemState _startMemState;
	};
}
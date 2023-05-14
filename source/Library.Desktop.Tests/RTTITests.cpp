#pragma once

#include "pch.h"
#include "CppUnitTest.h"

#include <cstddef>

#include "RTTI.h"
#include "Foo.h"
#include "Bar.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{

}
namespace LibraryDesktopTests
{
	TEST_CLASS(RTTITests)
	{
		TEST_METHOD(RTTIIs)
		{
			UnitTests::Foo a(10);
			RTTI::IdType FooId = a.TypeIdInstance();
			UnitTests::Bar x(10);
			RTTI::IdType BarId = x.TypeIdInstance();

			RTTI* aa = &a;

			Assert::IsTrue(aa->Is(FooId));
			Assert::IsTrue(!aa->Is(BarId));
		}
		TEST_METHOD(RTTIToString)
		{
			UnitTests::Foo a(10);

			Assert::IsTrue(a.ToString() == "RTTI");
		}
		TEST_METHOD(RTTIAs)
		{
			UnitTests::Foo a(10);
			UnitTests::Bar x(10);
			const UnitTests::Bar y(10);

			RTTI* aa = &a;
			RTTI* xx = &x;
			const RTTI* yy = &y;

			Assert::IsTrue(a.Equals(aa->As<Foo>()));
			Assert::IsTrue(xx->As<Foo>() == nullptr);
			Assert::IsTrue(yy->As<Foo>() == nullptr);
		}
		TEST_METHOD(Equals)
		{
			UnitTests::Bar x(10);
			RTTI* xx = &x;

			Assert::IsTrue(xx->Equals(xx));
		}
	};
}
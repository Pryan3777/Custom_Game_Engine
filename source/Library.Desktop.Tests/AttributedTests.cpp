#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedBar.h"
#include "AttributedFoo.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(AttributedTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

			TypeManager::CreateInstance();
			RegisterType<Attributed, Attributed>();
			RegisterType<AttributedFoo, Attributed>();
			RegisterType<AttributedBar, AttributedFoo>();
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			TypeManager::DestroyInstance();

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

		TEST_METHOD(Constructor)
		{
			AttributedFoo f;
			f["extra"];
			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(14));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(14));
			
			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}

		TEST_METHOD(CopyConstructor)
		{
			AttributedFoo e;
			e["extra"];

			AttributedFoo f(e);

			Assert::IsTrue(e == f);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(14));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(14));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));

		}

		TEST_METHOD(AssignmentOperator)
		{
			AttributedFoo e;
			e["extra"];

			AttributedFoo f;
			f = e;

			Assert::IsTrue(e == f);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(14));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(14));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}

		TEST_METHOD(MoveConstructor)
		{
			AttributedFoo e;
			e["extra"];

			AttributedFoo f(std::move(e));

			Assert::IsTrue(f != e);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(14));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(13));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(14));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}



		TEST_METHOD(BarConstructor)
		{
			AttributedBar f;
			f["extra"];
			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(15));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(15));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}

		TEST_METHOD(BarCopyConstructor)
		{
			AttributedBar e;
			e["extra"];

			AttributedBar f(e);

			Assert::IsTrue(e == f);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(15));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(15));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));

		}

		TEST_METHOD(BarAssignmentOperator)
		{
			AttributedBar e;
			e["extra"];

			AttributedBar f;
			f = e;

			Assert::IsTrue(e == f);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(15));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(15));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}

		TEST_METHOD(BarMoveConstructor)
		{
			AttributedBar e;
			e["extra"];

			AttributedBar f(std::move(e));

			Assert::IsTrue(f != e);

			Assert::AreEqual(f.Attributes().first, size_t(0));
			Assert::AreEqual(f.Attributes().second, size_t(15));
			Assert::AreEqual(f.PrescribedAttributes().first, size_t(0));
			Assert::AreEqual(f.PrescribedAttributes().second, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().first, size_t(14));
			Assert::AreEqual(f.AuxiliaryAttributes().second, size_t(15));

			Assert::IsTrue(f.IsAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAttribute("extra"));
			Assert::IsFalse(f.IsAttribute("none"));

			Assert::IsTrue(f.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsFalse(f.IsPrescribedAttribute("extra"));
			Assert::IsFalse(f.IsPrescribedAttribute("none"));

			Assert::IsFalse(f.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsTrue(f.IsAuxiliaryAttribute("extra"));
			Assert::IsFalse(f.IsAuxiliaryAttribute("none"));
		}

		

		



	private:
		_CrtMemState _startMemState;
	};
}
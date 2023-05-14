#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "Factory.h"
#include "AttributedFoo.h"
#include "AttributedFooFactory.h"
#include "TypeManager.h"
#include "JsonTableParseHelper.h"
#include "ConcreteFactory.mac"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;
using namespace UnitTests;

namespace LibraryDesktopTests
{
	TEST_CLASS(AttributedParserTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
			ConcreteFactory(AttributedFoo, Scope);

			TypeManager::CreateInstance();
			RegisterType<Attributed, Attributed>();
			RegisterType<AttributedFoo, Attributed>();
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			Factory<Scope>::Clear();
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

		TEST_METHOD(BasicParsing)
		{
			string inputString = R"({
	"table": {
		"type": "Table",
		"class": "AttributedFoo",
		"value": {
		}
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(13));
		}
		TEST_METHOD(ExtraParsing)
		{
			string inputString = R"({
	"table": {
		"type": "Table",
		"class": "AttributedFoo",
		"value": {
			"extraInt" : {
				"type" : "Integer",
				"value" : 1
			},
			"extraFloat" : {
				"type" : "Float",
				"value" : 1.0
			},
			"extraString" : {
				"type" : "String",
				"value" : "test"
			},
			"extraVec" : {
				"type" : "Vector",
				"value" : "[1.0, 1.0, 1.0, 1.0]"
			},
			"extraMat": {
				"type": "Matrix",
				"value": "[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]"
			},
			"extraTable": {
				"type": "Table",
				"class": "AttributedFoo",
				"value": {}
			}
		}
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(19));
		}
		TEST_METHOD(OverrideParsing)
		{
			string inputString = R"({
	"table": {
		"type": "Table",
		"class": "AttributedFoo",
		"value": {
			"ExternalInteger" : {
				"type" : "Integer",
				"value" : 10
			},
			"ExternalFloat" : {
				"type" : "Float",
				"value" : 10.0
			},
			"ExternalString" : {
				"type" : "String",
				"value" : "ten"
			},
			"ExternalVector" : {
				"type" : "Vector",
				"value" : "[1.0, 1.0, 1.0, 1.0]"
			},
			"ExternalMatrix": {
				"type": "Matrix",
				"value": "[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]"
			},
			"NestedScope": {
				"type": "Table",
				"value": {}
			}
		}
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(1));
			Scope* table = root->Append("table").GetScope(0);
			Assert::AreEqual(table->Size(), size_t(13));
			Assert::AreEqual(table->Append("ExternalInteger").GetInt(), 10);
			Assert::AreEqual(table->Append("ExternalFloat").GetFloat(), 10.0f);
		}

	private:
		_CrtMemState _startMemState;
	};
};
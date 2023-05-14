#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "Attributed.h"
#include "TypeManager.h"
#include "JsonTableParseHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(TableParserTests)
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

		TEST_METHOD(BasicParsing)
		{
			string inputString = R"({
	"int": {
		"type": "Integer",
		"value": 100
	},
	"float": {
		"type": "Float",
		"value": 10.01
	},
	"string": {
		"type": "String",
		"value": "test"
	},
	"vec": {
		"type": "Vector",
		"value": "[1.0, 1.0, 1.0, 1.0]"
	},
	"mat": {
		"type": "Matrix",
		"value": "[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]"
	},
	"table": {
		"type": "Table",
		"value": {
			"int": {
				"type": "Integer",
				"value": 200
			},
			"float": {
				"type": "Float",
				"value": 20.02
			},
			"string": {
				"type": "String",
				"value": "test2"
			},
			"vec": {
				"type": "Vector",
				"value": "[2.0, 2.0, 2.0, 2.0]"
			},
			"mat": {
				"type": "Matrix",
				"value": "[[2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0]]"
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
			Assert::AreEqual(root->Size(), size_t(6));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(5));

			Assert::AreEqual((*root)["int"].GetInt(0), 100);
			Assert::AreEqual((*root)["float"].GetFloat(0), 10.01f);
			Assert::AreEqual((*root)["string"].GetString(0), std::string("test"));
			Assert::IsTrue((*root)["vec"].GetVec(0) == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue((*root)["mat"].GetMat(0) == glm::mat4(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

			auto* table = (*root)["table"].GetScope(0);

			Assert::AreEqual((*table)["int"].GetInt(0), 200);
			Assert::AreEqual((*table)["float"].GetFloat(0), 20.02f);
			Assert::AreEqual((*table)["string"].GetString(0), std::string("test2"));
			Assert::IsTrue((*table)["vec"].GetVec(0) == glm::vec4(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue((*table)["mat"].GetMat(0) == glm::mat4(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f)));


		}

		TEST_METHOD(BasicFileParsing)
		{
			string inputString = R"({
	"int": {
		"type": "Integer",
		"value": 100
	},
	"float": {
		"type": "Float",
		"value": 10.01
	},
	"string": {
		"type": "String",
		"value": "test"
	},
	"vec": {
		"type": "Vector",
		"value": "[1.0, 1.0, 1.0, 1.0]"
	},
	"mat": {
		"type": "Matrix",
		"value": "[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]"
	},
	"table": {
		"type": "Table",
		"value": {
			"int": {
				"type": "Integer",
				"value": 200
			},
			"float": {
				"type": "Float",
				"value": 20.02
			},
			"string": {
				"type": "String",
				"value": "test2"
			},
			"vec": {
				"type": "Vector",
				"value": "[2.0, 2.0, 2.0, 2.0]"
			},
			"mat": {
				"type": "Matrix",
				"value": "[[2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0]]"
			}
		}
	}
})";

			const string inputFile = "test.json";
			std::ofstream outputFile(inputFile);

			outputFile << inputString;
			outputFile.close();

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObjectFromFile(inputFile);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(6));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(5));

			Assert::AreEqual((*root)["int"].GetInt(0), 100);
			Assert::AreEqual((*root)["float"].GetFloat(0), 10.01f);
			Assert::AreEqual((*root)["string"].GetString(0), std::string("test"));
			Assert::IsTrue((*root)["vec"].GetVec(0) == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue((*root)["mat"].GetMat(0) == glm::mat4(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

			auto* table = (*root)["table"].GetScope(0);

			Assert::AreEqual((*table)["int"].GetInt(0), 200);
			Assert::AreEqual((*table)["float"].GetFloat(0), 20.02f);
			Assert::AreEqual((*table)["string"].GetString(0), std::string("test2"));
			Assert::IsTrue((*table)["vec"].GetVec(0) == glm::vec4(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue((*table)["mat"].GetMat(0) == glm::mat4(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f)));


		}

		TEST_METHOD(ArrayParsing)
		{
			string inputString = R"({
	"int": {
		"type": "Integer",
		"value": [100, 200]
	},
	"float": {
		"type": "Float",
		"value": [10.01, 20.01]
	},
	"string": {
		"type": "String",
		"value": ["test", "test2"]
	},
	"vec": {
		"type": "Vector",
		"value": ["[1.0, 1.0, 1.0, 1.0]", "[1.1, 1.1, 1.1, 1.1]"]
	},
	"mat": {
		"type": "Matrix",
		"value": ["[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]", "[[1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.]]"]
	},
	"table": {
		"type": "Table",
		"value": [
{
	"int": {
		"type": "Integer",
		"value": [100, 200]
	},
	"float": {
		"type": "Float",
		"value": [10.01, 20.01]
	},
	"string": {
		"type": "String",
		"value": ["test", "test2"]
	},
	"vec": {
		"type": "Vector",
		"value": ["[1.0, 1.0, 1.0, 1.0]", "[1.1, 1.1, 1.1, 1.1]"]
	},
	"mat": {
		"type": "Matrix",
		"value": ["[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]", "[[1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.]]"]
	}
},
{
"int": {
		"type": "Integer",
		"value": [100, 200]
	},
	"float": {
		"type": "Float",
		"value": [10.01, 20.01]
	},
	"string": {
		"type": "String",
		"value": ["test", "test2"]
	},
	"vec": {
		"type": "Vector",
		"value": ["[1.0, 1.0, 1.0, 1.0]", "[1.1, 1.1, 1.1, 1.1]"]
	},
	"mat": {
		"type": "Matrix",
		"value": ["[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]", "[[1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.1], [1.1, 1.1, 1.1, 1.]]"]
	}
}
		]
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(6));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(5));
			Assert::AreEqual(root->Append("table")[1].Size(), size_t(5));
		}
		TEST_METHOD(ParserClone)
		{
			string inputString = R"({
	"int": {
		"type": "Integer",
		"value": 100
	},
	"float": {
		"type": "Float",
		"value": 10.01
	},
	"string": {
		"type": "String",
		"value": "test"
	},
	"vec": {
		"type": "Vector",
		"value": "[1.0, 1.0, 1.0, 1.0]"
	},
	"mat": {
		"type": "Matrix",
		"value": "[[1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 1.0]]"
	},
	"table": {
		"type": "Table",
		"value": {
			"int": {
				"type": "Integer",
				"value": 200
			},
			"float": {
				"type": "Float",
				"value": 20.02
			},
			"string": {
				"type": "String",
				"value": "test2"
			},
			"vec": {
				"type": "Vector",
				"value": "[2.0, 2.0, 2.0, 2.0]"
			},
			"mat": {
				"type": "Matrix",
				"value": "[[2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0], [2.0, 2.0, 2.0, 2.0]]"
			}
		}
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinatorInitial(wrapper);
			auto helper = make_shared<JsonTableParseHelper>();
			parseCoordinatorInitial.Initialize();
			helper->Initialize();
			parseCoordinatorInitial.AddHelper(helper);
			JsonParseCoordinator* parseCoordinator = parseCoordinatorInitial.Clone();


			parseCoordinatorInitial.Remove(helper);
			parseCoordinator->DeserializeObject(inputString);
			wrapper = parseCoordinator->GetWrapper();
			delete(parseCoordinator);

			
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;
			Assert::AreEqual(root->Size(), size_t(6));
			Assert::AreEqual(root->Append("table")[0].Size(), size_t(5));

			Assert::AreEqual((*root)["int"].GetInt(0), 100);
			Assert::AreEqual((*root)["float"].GetFloat(0), 10.01f);
			Assert::AreEqual((*root)["string"].GetString(0), std::string("test"));
			Assert::IsTrue((*root)["vec"].GetVec(0) == glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue((*root)["mat"].GetMat(0) == glm::mat4(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

			auto* table = (*root)["table"].GetScope(0);

			Assert::AreEqual((*table)["int"].GetInt(0), 200);
			Assert::AreEqual((*table)["float"].GetFloat(0), 20.02f);
			Assert::AreEqual((*table)["string"].GetString(0), std::string("test2"));
			Assert::IsTrue((*table)["vec"].GetVec(0) == glm::vec4(2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue((*table)["mat"].GetMat(0) == glm::mat4(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), glm::vec4(2.0f, 2.0f, 2.0f, 2.0f)));

		}

	private:
		_CrtMemState _startMemState;
	};
};
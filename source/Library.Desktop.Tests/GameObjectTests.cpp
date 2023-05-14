#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "Counter.h"
#include "TypeManager.h"
#include "JsonTableParseHelper.h"
#include "Factory.h"
#include "ConcreteFactory.mac"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(GameObjectTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

			ConcreteFactory(GameObject, Scope);
			ConcreteFactory(Counter, Scope);

			TypeManager::CreateInstance();
			RegisterType<Attributed, Attributed>();
			RegisterType<GameObject, Attributed>();
			RegisterType<Counter, GameObject>();
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

		TEST_METHOD(BasicGameObject)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

			Scope& counter = root->Append("game")[0];

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(counter.Size(), size_t(7));

			Assert::IsTrue(counter["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Scale"].GetVec() == glm::vec4());

			Assert::IsTrue(counter["Name"].GetString() == std::string("Game"));
		}
		TEST_METHOD(CloneGameObject)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

			GameObject * initialGameObject = root->Append("game")[0].As<GameObject>();

			Scope * copyGameObject = initialGameObject->Clone();

			Scope& counter = *copyGameObject;

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(counter.Size(), size_t(7));

			Assert::IsTrue(counter["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Scale"].GetVec() == glm::vec4());

			Assert::IsTrue(counter["Name"].GetString() == std::string("Game"));

			delete(copyGameObject);
		}
		TEST_METHOD(CopyConstructorGameObject)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

			GameObject* initialGameObject = root->Append("game")[0].As<GameObject>();

			GameObject copyGameObject(*initialGameObject);

			Scope& counter = copyGameObject;

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(counter.Size(), size_t(7));

			Assert::IsTrue(counter["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Scale"].GetVec() == glm::vec4());

			Assert::IsTrue(counter["Name"].GetString() == std::string("Game"));
		}
		TEST_METHOD(CopyAssignmentOperatorGameObject)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

			GameObject* initialGameObject = root->Append("game")[0].As<GameObject>();

			GameObject copyGameObject;
			copyGameObject = *initialGameObject;

			Assert::IsTrue(copyGameObject.Equals(initialGameObject));

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(copyGameObject.Size(), size_t(7));

			Assert::IsTrue(copyGameObject["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(copyGameObject["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(copyGameObject["Scale"].GetVec() == glm::vec4());

			Assert::IsTrue(copyGameObject["Name"].GetString() == std::string("Game"));

			std::string no = copyGameObject.ToString();
			no = "no";
			copyGameObject["Name"].Set(no);

			Assert::IsTrue(copyGameObject.Equals(initialGameObject) == false);
			
			Scope* s = new Scope;
			
			Assert::IsTrue(copyGameObject.Equals(s) == false);

			delete(s);
		}
		TEST_METHOD(IncorrectChild)
		{
			Assert::ExpectException<std::runtime_error>([]() {
				string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

				Scope& counter = root->Append("game")[0];

				Scope *s = new Scope;
				counter.Adopt(*s, "Children");

				GameTime g;

				GameObject* counterGameObject = (&counter)->As<GameObject>();
				counterGameObject->Update(g);
			});
		}

		TEST_METHOD(BasicCounter)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "Counter",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
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

			Scope& counter = root->Append("game")[0];

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(counter.Size(), size_t(8));

			Assert::IsTrue(counter["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Scale"].GetVec() == glm::vec4());

			Assert::IsTrue(counter["Name"].GetString() == std::string("Game"));

			Assert::AreEqual(counter["Count"].GetInt(), 0);
			
			GameTime g;

			GameObject* counterGameObject = (&counter)->As<GameObject>();
			counterGameObject->Update(g);

			Assert::AreEqual(counter["Count"].GetInt(), 1);
		}

		TEST_METHOD(NestedCounter)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "Counter",
		"value": {
			"Children": {
				"type": "Table",
				"class": "Counter",
				"value": {
					"Name" : {
						"type" : "String",
						"value" : "Game"
					}
				}
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

			Scope& counter = root->Append("game")[0];

			Assert::AreEqual(root->Size(), size_t(1));
			Assert::AreEqual(counter.Size(), size_t(8));

			Assert::IsTrue(counter["Position"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Rotation"].GetVec() == glm::vec4());
			Assert::IsTrue(counter["Scale"].GetVec() == glm::vec4());

			Assert::AreEqual(counter["Count"].GetInt(), 0);

			GameTime g;

			GameObject* counterGameObject = (&counter)->As<GameObject>();
			counterGameObject->Update(g);

			Assert::AreEqual(counter["Count"].GetInt(), 1);

			Scope& child = counter["Children"][0];

			Assert::AreEqual(child["Count"].GetInt(), 1);

			counterGameObject->Update(g);

			Assert::AreEqual(child["Count"].GetInt(), 2);
		}
		
	private:
		_CrtMemState _startMemState;
	};
};
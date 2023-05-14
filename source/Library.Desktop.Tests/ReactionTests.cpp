#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "Counter.h"
#include "TypeManager.h"
#include "JsonTableParseHelper.h"
#include "Factory.h"
#include "ConcreteFactory.mac"
#include "GameState.h"
#include "ReactionAttributed.h"
#include "EventQueue.h"
#include "ActionEvent.h"
#include "ActionList.h"
#include "ActionIncrement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ReactionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

			ConcreteFactory(GameObject, Scope);
			ConcreteFactory(ReactionAttributed, Scope);
			ConcreteFactory(ActionEvent, Scope);
			ConcreteFactory(ActionList, Scope);
			ConcreteFactory(ActionIncrement, Scope);

			TypeManager::CreateInstance();
			RegisterType<Attributed, Attributed>();
			RegisterType<GameObject, Attributed>();
			RegisterType<Action, Attributed>();
			RegisterType<ActionList, Action>();
			RegisterType<Reaction, ActionList>();
			RegisterType<ReactionAttributed, Reaction>();
			RegisterType<ActionEvent, Action>();
			RegisterType<ActionList, Action>();
			RegisterType<ActionIncrement, ActionList>();

			GameState::CreateInstance();

		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
			Factory<Scope>::Clear();
			TypeManager::DestroyInstance();
			GameState::DestroyInstance();

			EventQueue::Clear();

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

		TEST_METHOD(ReactionAndActionEvent)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Actions" : {
				"type": "Table",
				"class" : "ActionEvent",
				"value" : {
					"Subtype" : {
						"type" : "String",
						"value" : "TestSubtype"
					},
					"Auxiliary" : {
						"type" : "Integer",
						"value" : 123
					}
				}
			}
		}
	},
	"reaction": {
		"type": "Table",
		"class" : "ReactionAttributed",
		"value" : {
			"Subtype" : {
				"type" : "String",
				"value" : "TestSubtype"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionIncrement",
				"value" : {
					"Target" : {
						"type" : "String",
						"value" : "test"
					},
					"Value" : {
						"type" : "Integer",
						"value" : 1
					},
					"Index" : {
						"type" : "Integer",
						"value" : 0
					}
				}
			}
		}
	},
	"test" : {
		"type" : "Integer",
		"value" : 0
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;

			GameObject* g = root->Append("game")[0].As<GameObject>();
			Scope& react = root->Append("reaction")[0];
			Datum& test = root->Append("test");

			Assert::IsTrue(g != nullptr);
			Assert::IsTrue(react.Find("Auxiliary") == nullptr);
			
			g->Update(GameState::Instance()->Time());

			Assert::IsTrue(react.Find("Auxiliary") == nullptr);
			Assert::IsTrue(test.FrontInt() == 0);

			EventQueue::Update(GameState::Instance()->Time());

			Assert::IsTrue(react.Find("Auxiliary") != nullptr);
			Assert::AreEqual(react.Find("Auxiliary")->GetInt(), 123);
			
			Assert::IsTrue(test.FrontInt() == 1);
		}

		TEST_METHOD(ReactionAndActionEventDelay)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Actions" : {
				"type": "Table",
				"class" : "ActionEvent",
				"value" : {
					"Subtype" : {
						"type" : "String",
						"value" : "TestSubtype"
					},
					"Auxiliary" : {
						"type" : "Integer",
						"value" : 123
					},
					"Delay" : {
						"type" : "Integer",
						"value" : 10
					}
				}
			}
		}
	},
	"reaction": {
		"type": "Table",
		"class" : "ReactionAttributed",
		"value" : {
			"Subtype" : {
				"type" : "String",
				"value" : "TestSubtype"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionIncrement",
				"value" : {
					"Target" : {
						"type" : "String",
						"value" : "test"
					},
					"Value" : {
						"type" : "Integer",
						"value" : 1
					},
					"Index" : {
						"type" : "Integer",
						"value" : 0
					}
				}
			}
		}
	},
	"test" : {
		"type" : "Integer",
		"value" : 0
	}
})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonTableParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonTableParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonTableParseHelper::Wrapper* rawWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
			shared_ptr<Scope> root = rawWrapper->_root;

			GameObject* g = root->Append("game")[0].As<GameObject>();
			Scope& react = root->Append("reaction")[0];
			Datum& test = root->Append("test");

			Assert::IsTrue(g != nullptr);
			Assert::IsTrue(react.Find("Auxiliary") == nullptr);

			g->Update(GameState::Instance()->Time());

			Assert::IsTrue(react.Find("Auxiliary") == nullptr);
			Assert::IsTrue(test.FrontInt() == 0);

			EventQueue::Update(GameState::Instance()->Time());

			Assert::IsTrue(react.Find("Auxiliary") == nullptr);
			Assert::IsTrue(test.FrontInt() == 0);

			GameTime t(GameState::Instance()->Time());
			t.SetCurrentTime(t.CurrentTime() + std::chrono::duration<int, std::ratio<1, 1000>>(10));
			GameState::Instance()->SetGameTime(t);
			EventQueue::Update(GameState::Instance()->Time());

			Assert::IsTrue(react.Find("Auxiliary") != nullptr);
			Assert::AreEqual(react.Find("Auxiliary")->GetInt(), 123);

			Assert::IsTrue(test.FrontInt() == 1);
		}

	private:
		_CrtMemState _startMemState;
	};
};
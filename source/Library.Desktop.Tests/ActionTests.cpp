#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "TypeManager.h"
#include "JsonTableParseHelper.h"
#include "Factory.h"
#include "ConcreteFactory.mac"

#include "GameObject.h"
#include "ActionIncrement.h"
#include "ActionIf.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ActionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{

#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif

			ConcreteFactory(GameObject, Scope);
			ConcreteFactory(ActionList, Scope)
			ConcreteFactory(ActionIncrement, Scope);
			ConcreteFactory(ActionIf, Scope);

			TypeManager::CreateInstance();
			RegisterType<Attributed, Attributed>();
			RegisterType<GameObject, Attributed>();
			RegisterType<Action, Attributed>();
			RegisterType<ActionList, Action>();
			RegisterType<ActionIncrement, ActionList>();
			RegisterType<ActionIf, ActionList>();
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

		TEST_METHOD(BasicActionIncrement)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionIncrement",
				"value" :
				{
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

			GameObject* game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(1, test);
		}

		TEST_METHOD(DoubleActionIncrement)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionIncrement",
				"value" : [
				{
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
				},
				{
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
				]
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

			GameObject* game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(2, test);

			Assert::IsTrue(root->Append("game")[0].Append("Actions")[0].Equals(&root->Append("game")[0].Append("Actions")[1]));
		}

		TEST_METHOD(BasicActionList)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionList",
				"value" : {
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

			GameObject * game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(1, test);
		}

		TEST_METHOD(DoubleActionList)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : 
			{
				"type" : "Table",
				"class" : "ActionList",
				"value" : 
				[{
					"Actions" :
					{
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : 
						{
							"Target" : 
							{
								"type" : "String",
								"value" : "test"
							},
							"Value" : 
							{
								"type" : "Integer",
								"value" : 1
							},
							"Index" : 
							{
								"type" : "Integer",
								"value" : 0
							}
						}
					}
				},
				{
					"Actions" :
					{
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : 
						{
							"Target" : 
							{
								"type" : "String",
								"value" : "test"
							},
							"Value" : 
							{
								"type" : "Integer",
								"value" : 2
							},
							"Index" : 
							{
								"type" : "Integer",
								"value" : 0
							}
						}
					}
				}]
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

			GameObject* game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(3, test);
		}

		TEST_METHOD(CloneActionList)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : 
			{
				"type" : "Table",
				"class" : "ActionList",
				"value" : 
				[{
					"Actions" :
					{
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : 
						{
							"Target" : 
							{
								"type" : "String",
								"value" : "test"
							},
							"Value" : 
							{
								"type" : "Integer",
								"value" : 1
							},
							"Index" : 
							{
								"type" : "Integer",
								"value" : 0
							}
						}
					}
				},
				{
					"Actions" :
					{
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : 
						{
							"Target" : 
							{
								"type" : "String",
								"value" : "test"
							},
							"Value" : 
							{
								"type" : "Integer",
								"value" : 2
							},
							"Index" : 
							{
								"type" : "Integer",
								"value" : 0
							}
						}
					}
				}]
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

			GameObject* game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(3, test);

			Scope * s = game->Append("Actions")[1].As<ActionList>()->Clone();
			game->Adopt(*s, "Actions");

			Assert::IsTrue(game->Append("Actions")[1].As<ActionList>()->Equals(s));

			game->Update(g);

			Assert::AreEqual(8, test);

			Scope* t = game->Append("Actions")[0].Append("Actions")[0].As <ActionIncrement>()->Clone();
			game->Adopt(*t, "Actions");

			game->Update(g);
			Assert::AreEqual(14, test);

			Assert::AreEqual(game->Append("Actions")[0].Append("Actions")[0].ToString(), game->Append("Actions")[0].ToString());
		}

		TEST_METHOD(BasicActionIf)
		{
			string inputString = R"({
	"game": {
		"type": "Table",
		"class": "GameObject",
		"value": {
			"Name" : {
				"type" : "String",
				"value" : "Game"
			},
			"Actions" : {
				"type" : "Table",
				"class" : "ActionIf",
				"value" :
				{
					"Then" : {
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : [
						{
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
						},
						{
							"Target" : {
								"type" : "String",
								"value" : "Condition"
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
						]
					},
					"Else" : {
						"type" : "Table",
						"class" : "ActionIncrement",
						"value" : [
						{
							"Target" : {
								"type" : "String",
								"value" : "test"
							},
							"Value" : {
								"type" : "Integer",
								"value" : -1
							},
							"Index" : {
								"type" : "Integer",
								"value" : 0
							}
						},
						{
							"Target" : {
								"type" : "String",
								"value" : "Condition"
							},
							"Value" : {
								"type" : "Integer",
								"value" : -1
							},
							"Index" : {
								"type" : "Integer",
								"value" : 0
							}
						}
						]
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

			GameObject* game = root->Append("game")[0].As<GameObject>();
			int& test = root->Append("test").GetInt(0);

			Assert::AreEqual(root->Size(), size_t(2));
			Assert::AreEqual(game->Size(), size_t(7));

			Assert::AreEqual(0, test);

			GameTime g;
			game->Update(g);

			Assert::AreEqual(1, test);

			game->Update(g);

			Assert::AreEqual(0, test);

			Scope* s = game->Append("Actions")[0].Clone();
			game->Adopt(*s, "Actions");

			game->Update(g);

			Assert::AreEqual(2, test);

			game->Update(g);

			Assert::AreEqual(0, test);

			Assert::IsTrue(game->Append("Actions")[0].Equals(s));
			Assert::AreEqual(game->Append("Actions")[0].ToString(), game->Append("Actions")[1].ToString());
		}

	private:
		_CrtMemState _startMemState;
	};
};
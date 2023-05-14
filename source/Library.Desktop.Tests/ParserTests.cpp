#include "pch.h"
#include "CppUnitTest.h"
#include <cassert>

#include "memory"
#include "Attributed.h"
#include "TypeManager.h"
#include "JsonIntegerParseHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace std::string_literals;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ParserTests)
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

		TEST_METHOD(IntParsing)
		{
			string inputString = R"({ "integer": 100 })";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonIntegerParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonIntegerParseHelper>());

			parseCoordinator.DeserializeObject(inputString);
			JsonIntegerParseHelper::Wrapper* rawWrapper = static_cast<JsonIntegerParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->_data.Size());
			Assert::AreEqual(100, rawWrapper->_data.Front());
		}
		TEST_METHOD(FileIntParsing)
		{
			string inputString = R"({ "integer": 100 })";

			const string inputFile = "test.json";
			std::ofstream outputFile(inputFile);

			outputFile << inputString;
			outputFile.close();


			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonIntegerParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonIntegerParseHelper>());

			parseCoordinator.DeserializeObjectFromFile(inputFile);
			JsonIntegerParseHelper::Wrapper* rawWrapper = static_cast<JsonIntegerParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->_data.Size());
			Assert::AreEqual(100, rawWrapper->_data.Front());
		}
		TEST_METHOD(ObjectDepthParsing)
		{
			string inputString = R"({
				"Root" : { "Next": {"int" : 100}}
			})";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonIntegerParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			auto helper = make_shared<JsonIntegerParseHelper>();
			parseCoordinator.AddHelper(helper);
			parseCoordinator.Initialize();

			parseCoordinator.DeserializeObject(inputString);
			JsonIntegerParseHelper::Wrapper* rawWrapper = static_cast<JsonIntegerParseHelper::Wrapper*>(wrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->_data.Size());
			Assert::AreEqual(100, rawWrapper->_data.Front());
			Assert::AreEqual(size_t(2), rawWrapper->MaxDepth());
			Assert::AreEqual(size_t(1), rawWrapper->StartHandlerCount());
			Assert::AreEqual(size_t(1), rawWrapper->EndHandlerCount());

			parseCoordinator.Remove(helper);
		}
		TEST_METHOD(IntCloneParsing)
		{
			string inputString = R"({ "integer": 100 })";

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<JsonIntegerParseHelper::Wrapper>();
			JsonParseCoordinator parseCoordinator(wrapper);
			parseCoordinator.AddHelper(make_shared<JsonIntegerParseHelper>());

			auto copyCoordinator = parseCoordinator.Clone();

			copyCoordinator->DeserializeObject(inputString);
			auto copyWrapper = copyCoordinator->GetWrapper();
			JsonIntegerParseHelper::Wrapper* rawWrapper = static_cast<JsonIntegerParseHelper::Wrapper*>(copyWrapper.get());
			Assert::AreEqual(size_t(1), rawWrapper->_data.Size());
			Assert::AreEqual(100, rawWrapper->_data.Front());
			delete(copyCoordinator);
		}



	private:
		_CrtMemState _startMemState;
	};
};
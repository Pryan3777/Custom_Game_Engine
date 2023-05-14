#include "pch.h"
//#include "JsonIntegerParseHelper.h"
//
//namespace UnitTests
//{
//	RTTI_DEFINITIONS(JsonIntegerParseHelper::Wrapper);
//
//	std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> JsonIntegerParseHelper::Wrapper::Create() const
//	{
//		return std::make_shared<UnitTests::JsonIntegerParseHelper::Wrapper>();
//	}
//
//	bool JsonIntegerParseHelper::StartHandler(std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> wrapper, const std::string& key, Json::Value& value, bool isArray)
//	{
//		if (isArray || !value.isInt() || wrapper->As<FieaGameEngine::JsonParseCoordinator::Wrapper>() == nullptr)
//		{
//			return false;
//		}
//		wrapper->IncrementStartHandler();
//		wrapper->CheckString(key);
//		
//		static_cast<JsonIntegerParseHelper::Wrapper*>(wrapper.get())->_data.PushBack(value.asInt());
//		
//		return true;
//	}
//
//	bool JsonIntegerParseHelper::EndHandler(std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> wrapper, const std::string& key)
//	{
//		//REMOVE IF NOT USED
//		key;
//
//		wrapper->IncrementEndHandler();
//		
//		return true;
//	}
//
//	std::shared_ptr<FieaGameEngine::JsonParseHelper> JsonIntegerParseHelper::Create() const
//	{
//		return std::make_shared<JsonIntegerParseHelper>();
//	}
//
//}
#include "pch.h"
#include "JsonTableParseHelper.h"
#include "Factory.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper::Wrapper);

	JsonTableParseHelper::Wrapper::Wrapper()
	{
		_root = std::make_shared<Scope>();
		_stack.push(_root.get());
	}

	std::shared_ptr<FieaGameEngine::JsonParseCoordinator::Wrapper> JsonTableParseHelper::Wrapper::Create() const
	{
		return std::make_shared<JsonTableParseHelper::Wrapper>();
	}
	
	bool JsonTableParseHelper::StartHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, const std::string& key, Json::Value& value, bool isArray, int index)
	{
		if (wrapper->As<FieaGameEngine::JsonTableParseHelper::Wrapper>() == nullptr)
		{
			return false;
		}

		JsonTableParseHelper::Wrapper *tableWrapper = static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get());
		std::string search = value["type"].asString();
		auto findResult = tableWrapper->_handleTable.Find(value["type"].asString());
		assert(findResult != tableWrapper->_handleTable.end());

		findResult->second(tableWrapper, key, value, isArray, index);

		return true;
	}

	bool JsonTableParseHelper::EndHandler(std::shared_ptr<JsonParseCoordinator::Wrapper> wrapper, bool isTable)
	{
		if (isTable)
		{
			static_cast<JsonTableParseHelper::Wrapper*>(wrapper.get())->_stack.pop();
		}
		return true;
	}

	std::shared_ptr<JsonParseHelper> JsonTableParseHelper::Create() const
	{
		return std::make_shared<JsonTableParseHelper>();
	}

	float JsonTableParseHelper::Wrapper::FloatParse(std::string& string)
	{
		string.erase(0, string.find_first_not_of(" \t\n\r\f\v"));
		bool period = true;
		bool first = true;
		std::string result = "";
		while (isdigit(string[0]) || (string[0] == '-' && first) || (string[0] == '.' && period))
		{
			if (string[0] == '.')
			{
				period = false;
			}
			first = false;
			
			result += string[0];
			string.erase(0, 1);
		}
		return stof(result);
	}

	glm::vec4 JsonTableParseHelper::Wrapper::VecParse(std::string &string)
	{
		string.erase(0, string.find_first_not_of(" \t\n\r\f\v"));
		string.erase(0, 1);

		float a = FloatParse(string);
		string.erase(0, 1);
		float b = FloatParse(string);
		string.erase(0, 1);
		float c = FloatParse(string);
		string.erase(0, 1);
		float d = FloatParse(string);

		string.erase(0, 1);

		return glm::vec4(a, b, c, d);
	}

	glm::mat4 JsonTableParseHelper::Wrapper::MatParse(std::string &string)
	{
		string.erase(0, string.find_first_not_of(" \t\n\r\f\v"));
		string.erase(0, 1);

		glm::vec4 a = VecParse(string);
		string.erase(0, 1);
		glm::vec4 b = VecParse(string);
		string.erase(0, 1);
		glm::vec4 c = VecParse(string);
		string.erase(0, 1);
		glm::vec4 d = VecParse(string);

		string.erase(0, 1);

		return glm::mat4(a, b, c, d);
	}

	void JsonTableParseHelper::Wrapper::Integer(JsonTableParseHelper::Wrapper *wrapper, const std::string& string, Json::Value rawValue, bool isArray, int index)
	{
		Json::Value value = rawValue["value"];
		int i;
		if (isArray)
		{
			assert(value[index].isInt());
			i = value[index].asInt();
		}
		else
		{
			assert(value.isInt());
			i = value.asInt();
		}
		
		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::Integer);
		}

		if (existingDatum->isExternal())
		{
			existingDatum->GetInt(index) = i;
		}
		else
		{
			existingDatum->PushBack(i);
		}
	}

	void JsonTableParseHelper::Wrapper::Float(JsonTableParseHelper::Wrapper* wrapper, const std::string& string, Json::Value rawValue, bool isArray, int index)
	{
		Json::Value value = rawValue["value"];
		float f;
		if (isArray)
		{
			assert(value[index].isNumeric());
			f = value[index].asFloat();
		}
		else
		{
			assert(value.isNumeric());
			f = value.asFloat();
		}
		
		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::Float);
		}

		if (existingDatum->isExternal())
		{
			existingDatum->GetFloat(index) = f;
		}
		else
		{
			existingDatum->PushBack(f);
		}
	}

	void JsonTableParseHelper::Wrapper::String(JsonTableParseHelper::Wrapper* wrapper, const std::string& string, Json::Value rawValue, bool isArray, int index)
	{
		Json::Value value = rawValue["value"];
		std::string s;
		if (isArray)
		{
			assert(value[index].isString());
			s = value[index].asString();
		}
		else
		{
			assert(value.isString());
			s = value.asString();
		}
		
		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::String);
		}

		if (existingDatum->isExternal())
		{
			existingDatum->GetString(index) = s;
		}
		else
		{
			existingDatum->PushBack(s);
		}
	}

	void JsonTableParseHelper::Wrapper::Vector(JsonTableParseHelper::Wrapper* wrapper, const std::string& string, Json::Value rawValue, bool isArray, int index)
	{
		Json::Value value = rawValue["value"];
		std::string s;
		if (isArray)
		{
			assert(value[index].isString());
			s = value[index].asString();
		}
		else
		{
			assert(value.isString());
			s = value.asString();
		}
		

		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::Vector);
		}

		if (existingDatum->isExternal())
		{
			existingDatum->GetVec(index) = VecParse(s);
		}
		else
		{
			existingDatum->PushBack(VecParse(s));
		}
	}

	void JsonTableParseHelper::Wrapper::Matrix(JsonTableParseHelper::Wrapper* wrapper, const std::string& string, Json::Value rawValue, bool isArray, int index)
	{
		Json::Value value = rawValue["value"];
		std::string s;
		if (isArray)
		{
			assert(value[index].isString());
			s = value[index].asString();
		}
		else
		{
			assert(value.isString());
			s = value.asString();
		}

		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::Matrix);
		}

		if (existingDatum->isExternal())
		{
			existingDatum->GetMat(index) = MatParse(s);
		}
		else
		{
			existingDatum->PushBack(MatParse(s));
		}		
	}

	void JsonTableParseHelper::Wrapper::Table(JsonTableParseHelper::Wrapper* wrapper, const std::string& string, [[maybe_unused]] Json::Value value, [[maybe_unused]] bool isArray, [[maybe_unused]] int index)
	{
		Scope* top = wrapper->_stack.top();
		Datum* existingDatum = top->Find(string);

		Scope* scopeToAdd;
		if (value.isMember("class"))
		{
			const std::string className = value["class"].asString();
			scopeToAdd = Factory<Scope>::Create(className);
		}
		else
		{
			scopeToAdd = new Scope;
		}

		if (existingDatum == nullptr)
		{
			existingDatum = &top->Append(string);
			existingDatum->SetType(Datum::DatumTypes::Table);
		}

		top->Adopt(*scopeToAdd, string);

		wrapper->_stack.push(scopeToAdd);
	}

}


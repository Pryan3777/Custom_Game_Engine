#include "pch.h"
#include "JsonParseCoordinator.h"
#include "JsonParseHelper.h"

#include <iostream>
#include <direct.h>

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonParseCoordinator::Wrapper);

	JsonParseCoordinator::JsonParseCoordinator(std::shared_ptr<Wrapper> wrapper)
	{
		SetWrapper(wrapper);
		wrapper->SetJsonParseCoordinator(this);
	}

	[[nodiscard]] JsonParseCoordinator* JsonParseCoordinator::Clone() const
	{
		std::shared_ptr<Wrapper> wrapper = GetWrapper()->Create();
		JsonParseCoordinator *coordinator = new JsonParseCoordinator(wrapper);
		for (size_t i = 0; i < _helpers.Size(); i++)
		{
			coordinator->AddHelper(_helpers[i]->Create());
		}
		coordinator->_cloned = true;
		return coordinator;
	}

	void JsonParseCoordinator::AddHelper(std::shared_ptr<JsonParseHelper> helper)
	{
		_helpers.PushBack(helper);
	}

	void JsonParseCoordinator::Remove(std::shared_ptr<JsonParseHelper> target)
	{
		_helpers.Remove(_helpers.Find(target));
	}

	void JsonParseCoordinator::DeserializeObject(const std::string &data)
	{
		std::istringstream stream(data);
		DeserializeObject(stream);
	}

	void JsonParseCoordinator::DeserializeObjectFromFile(const std::string &file)
	{
		std::ifstream ifs(file);
		DeserializeObject(ifs);
	}

	void JsonParseCoordinator::DeserializeObject(std::istream &stream)
	{
		Json::Value root;
		stream >> root;

		ParseMembers(root);
	}

	void JsonParseCoordinator::SetWrapper(std::shared_ptr<Wrapper> wrapper)
	{
		_wrapper = wrapper;
	}

	void JsonParseCoordinator::Initialize()
	{
		for (size_t i = 0; i < _helpers.Size(); i++)
		{
			_helpers[i]->Initialize();
		}
	}

	std::shared_ptr<JsonParseCoordinator::Wrapper> JsonParseCoordinator::GetWrapper() const
	{
		return _wrapper;
	}

	void JsonParseCoordinator::ParseMembers(Json::Value value)
	{
		for (Json::Value::const_iterator it = value.begin(); it != value.end(); it++)
		{
			Parse(it.key().asString(), *it, (*it)["value"].isArray());
		}
	}

	void JsonParseCoordinator::Parse(const std::string& string, Json::Value value, bool isArray)
	{
		bool parsed = false;
		if (isArray)
		{
			for (int j = 0; j < static_cast<int>(value["value"].size()); j++)
			{
				for (size_t i = 0; i < _helpers.Size(); i++)
				{
					if (_helpers[i]->StartHandler(_wrapper, string, value, true, j))
					{
						parsed = true;
						if (value["type"] == "Table")
						{
							_wrapper->IncrementDepth();
							ParseMembers(value["value"][j]);
							_wrapper->DecrementDepth();
							_helpers[i]->EndHandler(_wrapper, true);
						}
						else
						{
							_helpers[i]->EndHandler(_wrapper, false);
						}

						break;
					}
				}
			}
		}
		else
		{
			for (size_t i = 0; i < _helpers.Size(); i++)
			{
				if (_helpers[i]->StartHandler(_wrapper, string, value))
				{
					parsed = true;

					if (value["type"] == "Table")
					{
						_wrapper->IncrementDepth();
						ParseMembers(value["value"]);
						_wrapper->DecrementDepth();
						_helpers[i]->EndHandler(_wrapper, true);
					}
					else
					{
						_helpers[i]->EndHandler(_wrapper, false);
					}

					break;
				}
			}
		}
		

		assert(parsed);
	}

	void JsonParseCoordinator::Wrapper::SetJsonParseCoordinator(JsonParseCoordinator *coordinator)
	{
		_coordinator = coordinator;
	}

	JsonParseCoordinator* JsonParseCoordinator::Wrapper::GetJsonParseCoordinator()
	{
		return _coordinator;
	}

	void JsonParseCoordinator::Wrapper::IncrementDepth()
	{
		++_depth;
	}

	void JsonParseCoordinator::Wrapper::DecrementDepth()
	{
		--_depth;
	}

}

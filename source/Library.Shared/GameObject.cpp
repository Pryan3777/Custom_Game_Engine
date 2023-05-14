#include "pch.h"

#include "GameObject.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject);

	GameObject::GameObject(RTTI::IdType type) :
		Attributed(type),
		_name(""),
		_position(),
		_rotation(),
		_scale()
	{

	}

	void GameObject::Update(GameTime time)
	{
		UpdateLocal(time);
		UpdateChildren(time);
	}

	void GameObject::UpdateLocal(GameTime time)
	{
		time;

	}

	void GameObject::UpdateChildren(GameTime time)
	{
		Datum& actions = _data["Actions"];
		for (int i = 0; i < (int)actions.Size(); ++i)
		{
			Action* child = actions[i].As<Action>();
			if (child == nullptr)
			{
				throw std::runtime_error("Game Object has Child that is not of type Game Object");
			}
			child->Update(time);
		}

		Datum& children = _data["Children"];
		for (int i = 0; i < (int)children.Size(); ++i)
		{
			GameObject* child = children[i].As<GameObject>();
			if (child == nullptr)
			{
				throw std::runtime_error("Game Object has Child that is not of type Game Object");
			}
			child->Update(time);
		}
	}

	Scope* GameObject::Clone()
	{
		return new GameObject(*this);
	}
	bool GameObject::Equals(const RTTI* rhs) const
	{
		auto as = rhs->As<GameObject>();
		if (as == nullptr)
		{
			return false;
		}

		return _name == as->_name &&
			_position == as->_position &&
			_rotation == as->_rotation &&
			_scale == as->_scale;
	}
	std::string GameObject::ToString() const
	{
		return std::string();
	}
	Vector<Signature> GameObject::Signatures()
	{
		return {
			{"Name", Datum::DatumTypes::String, 1, offsetof(GameObject, _name)},
			{"Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _position)},
			{"Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _rotation)},
			{"Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, _scale)},
			{"Children", Datum::DatumTypes::Table, 1, 1},
			{"Actions", Datum::DatumTypes::Table, 1, 1}
		};
	}
}


#include "pch.h"

#include "ActionIncrement.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement(RTTI::IdType type) :
		ActionList(type)
	{
	}
	void ActionIncrement::Update(GameTime time)
	{
		time;
		Datum *d = Search(_target);
		assert(d->Size() >= size_t(_index));
		d->GetInt(_index) += _value;
	}
	Scope* ActionIncrement::Clone()
	{
		return new ActionIncrement(*this);
	}
	bool ActionIncrement::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
		{
			return false;
		}
		auto as = rhs->As<ActionIncrement>();
		if (as == nullptr)
		{
			return false;
		}

		return 
			_value == as->_value &&
			_index == as->_index;
	}
	std::string ActionIncrement::ToString() const
	{
		return std::string();
	}
	Vector<Signature> ActionIncrement::Signatures()
	{
		return {
			{"Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, _target)},
			{"Value", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, _value)},
			{"Index", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, _index)}
		};
	}
}
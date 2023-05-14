#include "pch.h"

#include "ActionList.h"


namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);

	ActionList::ActionList(RTTI::IdType type) :
		Action(type)
	{
	}
	void ActionList::Update(GameTime time)
	{
		Datum& actions = _data["Actions"];
		for (size_t i = 0; i < actions.Size(); i++)
		{
			Action* action = _data["Actions"].GetScope(i)->As<Action>();
			assert(action != nullptr);
			action->Update(time);
		}
	}
	Scope* ActionList::Clone()
	{
		return new ActionList(*this);
	}
	bool ActionList::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
		{
			return false;
		}

		const ActionList *otherType = rhs->As<ActionList>();
		if (otherType == nullptr ||
			_data.ContainsKey("Actions") == false ||
			otherType->_data.ContainsKey("Actions") == false ||
			_data.At("Actions").Size() != otherType->_data.At("Actions").Size())
		{
			return false;
		}

		const Datum& a = _data.At("Actions");
		const Datum& b = otherType->_data.At("Actions");

		for (size_t i = 0; i < a.Size(); i++)
		{
			if (!a.GetScope(i)->Equals(b.GetScope(i)))
			{
				return false;
			}
		}

		return true;
	}
	std::string ActionList::ToString() const
	{
		return std::string();
	}
	Vector<Signature> ActionList::Signatures()
	{
		return {
			{"Actions", Datum::DatumTypes::Table, 1, 1}
		};
	}
}
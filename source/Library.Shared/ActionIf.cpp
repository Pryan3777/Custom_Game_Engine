#include "pch.h"

#include "ActionIf.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIf);

	ActionIf::ActionIf(RTTI::IdType type) :
		ActionList(type)
	{
	}
	void ActionIf::Update(GameTime time)
	{
		if (_condition == 0)
		{
			Datum& d = _data["Then"];
			for (int i = 0; size_t(i) < d.Size(); i++)
			{
				d[i].As<Action>()->Update(time);
			}
		}
		else
		{
			Datum& d = _data["Else"];
			for (int i = 0; size_t(i) < d.Size(); i++)
			{
				d[i].As<Action>()->Update(time);
			}
		}
	}
	Scope* ActionIf::Clone()
	{
		return new ActionIf(*this);
	}
	bool ActionIf::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
		{
			return false;
		}
		auto as = rhs->As<ActionIf>();
		if (as == nullptr)
		{
			return false;
		}

		return
			_condition == as->_condition;
	}
	std::string ActionIf::ToString() const
	{
		return std::string();
	}
	Vector<Signature> ActionIf::Signatures()
	{
		return {
			{"Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionIf, _condition)},
			{"Then", Datum::DatumTypes::Table, 1, 1},
			{"Else", Datum::DatumTypes::Table, 1, 1}
		};
	}
}
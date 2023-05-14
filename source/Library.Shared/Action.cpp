#include "pch.h"

#include "Action.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action);

	Action::Action(RTTI::IdType type) :
		Attributed(type),
		_name("")
	{

	}
	Vector<Signature> Action::Signatures()
	{
		return {
			{"Name", Datum::DatumTypes::String, 1, offsetof(Action, _name)}
		};
	}
}
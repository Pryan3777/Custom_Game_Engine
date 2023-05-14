#include "pch.h"

#include "ActionExpression.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionExpression);

	ActionExpression::ActionExpression(RTTI::IdType type) :
		ActionList(type)
	{
	}
	void ActionExpression::Update(GameTime time)
	{
		time;

	}
	Scope* ActionExpression::Clone()
	{
		return nullptr;
	}
	bool ActionExpression::Equals(const RTTI* rhs) const
	{
		rhs;
		return false;
	}
	std::string ActionExpression::ToString() const
	{
		return std::string();
	}
	Vector<Signature> ActionExpression::Signatures()
	{
		return Vector<Signature>();
	}
}
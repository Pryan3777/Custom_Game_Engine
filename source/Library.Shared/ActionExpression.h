#pragma once

#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionExpression : public ActionList
	{
		RTTI_DECLARATIONS(ActionExpression, ActionList);

	public:
		ActionExpression(RTTI::IdType type = TypeIdClass());
		ActionExpression(const ActionExpression& other) = default;
		ActionExpression& operator=(const ActionExpression& other) = default;

		virtual void Update(GameTime time) override;

		std::string _rpn;

		Scope* Clone() override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static Vector<Signature> Signatures();
	};
}
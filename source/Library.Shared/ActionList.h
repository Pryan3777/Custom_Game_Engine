#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "Action.h"
#include "GameClock.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	public:
		ActionList(RTTI::IdType type = TypeIdClass());
		ActionList(const ActionList& other) = default;
		ActionList& operator=(const ActionList& other) = default;

		virtual void Update(GameTime time) override;

		virtual Scope* Clone() override;
		virtual bool Equals(const RTTI* rhs) const override;
		virtual std::string ToString() const override;

		static Vector<Signature> Signatures();
	};
}
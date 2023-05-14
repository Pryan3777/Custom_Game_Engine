#pragma once

#include "GameObject.h"

using namespace FieaGameEngine;
namespace UnitTests
{
	class Counter : public FieaGameEngine::GameObject
	{
		RTTI_DECLARATIONS(Counter, FieaGameEngine::GameObject);

	public:
		Counter(RTTI::IdType type = TypeIdClass());
		Counter(const Counter& other) = default;
		Counter& operator=(const Counter& other) = default;

		int _count = 0;

		virtual void UpdateLocal(GameTime time) override;

		Scope* Clone() override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static Vector<Signature> Signatures();
	};
}
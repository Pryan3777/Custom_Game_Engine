#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "RTTI.h"
#include "AttributedFoo.h"
#include "Signature.h"
#include "Scope.h"

namespace UnitTests
{
	class AttributedBar : public AttributedFoo
	{
		RTTI_DECLARATIONS(AttributedBar, AttributedFoo);

	public:
		static const size_t ArraySize = 5;

		AttributedBar(RTTI::IdType type = TypeIdClass());
		AttributedBar(const AttributedBar&) = default;
		AttributedBar(AttributedBar&&) = default;
		AttributedBar& operator=(const AttributedBar&) = default;
		AttributedBar& operator=(AttributedBar&&) = default;
		~AttributedBar() = default;

		int BarInt = 0;

		Scope* Clone() override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};
}
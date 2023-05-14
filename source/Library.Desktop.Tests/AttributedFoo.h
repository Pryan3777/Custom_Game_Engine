#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "RTTI.h"
#include "Attributed.h"
#include "Signature.h"
#include "Scope.h"

namespace UnitTests
{
	class AttributedFoo : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed);

	public:
		static const size_t ArraySize = 5;

		AttributedFoo(RTTI::IdType type = TypeIdClass());
		AttributedFoo(const AttributedFoo& other) = default;
		AttributedFoo(AttributedFoo&& other) = default;
		AttributedFoo& operator=(const AttributedFoo& other) = default;
		AttributedFoo& operator=(AttributedFoo&& other) = default;
		~AttributedFoo() = default;
		
		int ExternalInteger = 0;
		float ExternalFloat = 0;
		std::string ExternalString;
		glm::vec4 ExternalVector;
		glm::mat4 ExternalMatrix;

		int ExternalIntegerArray[ArraySize];
		float ExternalFloatArray[ArraySize];
		std::string ExternalStringArray[ArraySize];
		glm::vec4 ExternalVectorArray[ArraySize];
		glm::mat4 ExternalMatrixArray[ArraySize];

		Scope* Clone() override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};
}
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

namespace FieaGameEngine
{
	class Transform : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(Transform, Attributed);

	public:
		Transform(RTTI::IdType type = TypeIdClass());
		Transform(const Transform& other) = default;
		Transform& operator=(const Transform& other) = default;

		glm::vec4 _position;
		glm::vec4 _rotation;
		glm::vec4 _scale;

		Scope* Clone() override;
		bool Equals(const RTTI* rhs) const override;
		std::string ToString() const override;

		static Vector<Signature> Signatures();
	};
}
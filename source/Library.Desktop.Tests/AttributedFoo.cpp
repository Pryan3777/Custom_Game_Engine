#include "pch.h"
#include "AttributedFoo.h"
#include <algorithm>

using namespace FieaGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedFoo);

	AttributedFoo::AttributedFoo(RTTI::IdType type) :
		Attributed(type),
		ExternalString(""),
		ExternalVector(glm::vec4()),
		ExternalMatrix(glm::mat4()),
		ExternalIntegerArray{0, 0, 0, 0, 0},
		ExternalFloatArray{0, 0, 0, 0, 0},
		ExternalStringArray{"", "", "", "", ""},
		ExternalVectorArray{glm::vec4(), glm::vec4(), glm::vec4(), glm::vec4(), glm::vec4()},
		ExternalMatrixArray{ glm::mat4(), glm::mat4(), glm::mat4(), glm::mat4(), glm::mat4()}
	{

	}

	Scope* AttributedFoo::Clone()
	{
		return new AttributedFoo(*this);
	}

	bool AttributedFoo::Equals(const RTTI* rhs) const
	{
		auto as = rhs->As<AttributedFoo>();
		if (as == nullptr)
		{
			return false;
		}

		return ExternalInteger == as->ExternalInteger &&
			ExternalFloat == as->ExternalFloat &&
			ExternalString == as->ExternalString &&
			ExternalVector == as->ExternalVector &&
			ExternalMatrix == as->ExternalMatrix &&
			std::equal(ExternalIntegerArray, ExternalIntegerArray + ArraySize, as->ExternalIntegerArray) &&
			std::equal(ExternalFloatArray, ExternalFloatArray + ArraySize, as->ExternalFloatArray) &&
			std::equal(ExternalStringArray, ExternalStringArray + ArraySize, as->ExternalStringArray) &&
			std::equal(ExternalVectorArray, ExternalVectorArray + ArraySize, as->ExternalVectorArray) &&
			std::equal(ExternalMatrixArray, ExternalMatrixArray + ArraySize, as->ExternalMatrixArray);
	}

	std::string AttributedFoo::ToString() const
	{
		return std::string();
	}

	Vector<Signature> AttributedFoo::Signatures()
	{
		return {
			{"ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger)},
			{"ExternalFloat", Datum::DatumTypes::Float  , 1, offsetof(AttributedFoo, ExternalFloat)},
			{"ExternalString", Datum::DatumTypes::String , 1, offsetof(AttributedFoo, ExternalString)},
			{"ExternalVector", Datum::DatumTypes::Vector , 1, offsetof(AttributedFoo, ExternalVector)},
			{"ExternalMatrix", Datum::DatumTypes::Matrix, 1, offsetof(AttributedFoo, ExternalMatrix)},

			{ "ExternalIntegerArray", Datum::DatumTypes::Integer, ArraySize, offsetof(AttributedFoo, ExternalIntegerArray) },
			{ "ExternalFloatArray", Datum::DatumTypes::Float  , ArraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalStringArray", Datum::DatumTypes::String , ArraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "ExternalVectorArray", Datum::DatumTypes::Vector , ArraySize, offsetof(AttributedFoo, ExternalVectorArray) },
			{ "ExternalMatrixArray", Datum::DatumTypes::Matrix, ArraySize, offsetof(AttributedFoo, ExternalMatrixArray) },

			{ "NestedScope", Datum::DatumTypes::Table, 0, 0 },
			{ "NestedScopeArray", Datum::DatumTypes::Table, ArraySize, 0 },
		};
	}
	
}
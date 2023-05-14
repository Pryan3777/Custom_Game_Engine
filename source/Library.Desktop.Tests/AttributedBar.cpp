#include "pch.h"
#include "AttributedBar.h"

using namespace FieaGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedBar);

	AttributedBar::AttributedBar(RTTI::IdType type) :
		AttributedFoo(type)
	{

	}

	Scope* AttributedBar::Clone()
	{
		return new AttributedBar(*this);
	}

	bool AttributedBar::Equals(const RTTI* rhs) const
	{
		auto as = rhs->As<AttributedBar>();
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
			std::equal(ExternalMatrixArray, ExternalMatrixArray + ArraySize, as->ExternalMatrixArray) &&
			BarInt == as->BarInt;
	}

	std::string AttributedBar::ToString() const
	{
		return std::string();
	}

	Vector<Signature> AttributedBar::Signatures()
	{
		return {
			{"BarInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedBar, BarInt)},
		};
	}

}
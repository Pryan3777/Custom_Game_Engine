#include "pch.h"

#include "Counter.h"

using namespace FieaGameEngine;
namespace UnitTests
{
	RTTI_DEFINITIONS(Counter);

	Counter::Counter(FieaGameEngine::RTTI::IdType type) :
		GameObject(type)
	{

	}
	void Counter::UpdateLocal(GameTime time)
	{
		time;
		_count++;
	}
	Scope* Counter::Clone()
	{
		return nullptr;
	}
	bool Counter::Equals(const RTTI* rhs) const
	{
		auto as = rhs->As<Counter>();
		if (as == nullptr)
		{
			return false;
		}

		return GameObject::Equals(rhs) &&
			_count == as->_count;
	}
	std::string Counter::ToString() const
	{
		return std::string();
	}
	Vector<Signature> Counter::Signatures()
	{
		return {
			{"Count", Datum::DatumTypes::Integer, 1, offsetof(Counter, _count)}
		};
	}
}


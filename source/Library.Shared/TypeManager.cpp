#include "pch.h"
#include "TypeManager.h"


namespace FieaGameEngine
{
	void TypeManager::Add(RTTI::IdType type, Vector<Signature> signatures, RTTI::IdType parentType)
	{
		type;
		signatures;
		parentType;
		if (type == parentType)
		{
			_signatures[type];
		}
		else
		{
			_signatures[type] = _signatures[parentType];
		}
		Vector<Signature>::Iterator ib = signatures.begin();
		Vector<Signature>::Iterator ie = signatures.end();
		for (ib; ib != ie; ++ib)
		{
			_signatures[type].PushBack(*ib);
		}
	}
	Vector<Signature>& TypeManager::GetSignaturesForTypeId(size_t typeId)
	{
		auto i = _signatures.begin();
		auto ia = *i;
		++i;
		auto ib = *i;
		return _signatures[typeId];
	}
}
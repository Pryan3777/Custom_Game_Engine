#include "pch.h"
#include "EventMessageAttributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed);

	EventMessageAttributed::EventMessageAttributed(RTTI::IdType type) :
		Attributed(type),
		_subtype("")
	{
	}

	FieaGameEngine::Vector<FieaGameEngine::Signature> EventMessageAttributed::Signatures()
	{
		return {
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(EventMessageAttributed, _subtype)}
		};
	}
}
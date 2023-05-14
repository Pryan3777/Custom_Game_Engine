#include "pch.h"
#include "ReactionAttributed.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed(RTTI::IdType type) :
		Reaction(type)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	void ReactionAttributed::Notify(EventPublisher* eventPublisher)
	{
		auto EventMessage = eventPublisher->As<Event<EventMessageAttributed>>()->Message();
		if (EventMessage["Subtype"].GetString() == Append("Subtype").GetString())
		{
			for (size_t i = EventMessage.AuxiliaryAttributes().first; i < EventMessage.AuxiliaryAttributes().second; ++i)
			{
				Append(EventMessage.FindName(i)) = EventMessage[i];
			}
			ActionList::Update(GameState::Instance()->Time());
		}
	}

	Vector<Signature> ReactionAttributed::Signatures()
	{
		return {
			{"Subtype", Datum::DatumTypes::String, 1, offsetof(ReactionAttributed, _subtype)}
		};
	}
}
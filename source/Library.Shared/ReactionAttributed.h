#pragma once
#include "Reaction.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include "GameState.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Reaction Attributed
	/// Automatically subscribes to events of type
	/// Event Message Attributed and copies datums
	/// to this one.
	/// </summary>
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);
	public:
		/// <summary>
		/// Constructor for RTTI
		/// </summary>
		/// <param name="type">RTTI Type</param>
		ReactionAttributed(RTTI::IdType type = TypeIdClass());
		~ReactionAttributed();

		/// <summary>
		/// Called by Event
		/// Triggers Copying from EventPublisher.Message
		/// to this Datum
		/// </summary>
		/// <param name="eventPublisher">Publisher that made Event call</param>
		virtual void Notify(EventPublisher* eventPublisher) override;

		/// <summary>
		/// Subtype to accept EventMessages from
		/// </summary>
		std::string _subtype;

		/// <summary>
		/// This Datum's Prescribed Attribute Signatures
		/// </summary>
		static Vector<Signature> Signatures();
	};
}
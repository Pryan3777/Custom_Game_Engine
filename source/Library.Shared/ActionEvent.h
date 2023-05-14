#pragma once
#include "Action.h"
#include "EventMessageAttributed.h"
#include "Event.h"
#include "EventQueue.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Action that Creates an Event on Update
	/// </summary>
	class ActionEvent : public Action
	{
	public:
		/// <summary>
		/// On Call, Creates an Attributed Event and Adds to Queue
		/// </summary>
		/// <param name="g">Game Time</param>
		virtual void Update(GameTime g) override;

		/// <summary>
		/// Event Message
		/// Payload for Event added to Queue
		/// </summary>
		EventMessageAttributed _message;

		/// <summary>
		/// Subtype of Messages Added
		/// </summary>
		std::string _subtype;

		/// <summary>
		/// Delay of Messages Added
		/// </summary>
		int _delay;

		/// <summary>
		/// Signatures of this Datum
		/// </summary>
		/// <returns>Signatures of this Datum</returns>
		static Vector<Signature> Signatures();
	};
}

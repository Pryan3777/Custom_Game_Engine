#pragma once
#include "Attributed.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Event Message Type
	/// Used for Reactoin and EventAction
	/// </summary>
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);

	public:
		/// <summary>
		/// Constructor for RTTI
		/// </summary>
		/// <param name="type">type of this object</param>
		EventMessageAttributed(RTTI::IdType type = TypeIdClass());

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Object to Copy</param>
		EventMessageAttributed(const EventMessageAttributed& other) = default;

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">Object to Move From</param>
		EventMessageAttributed(EventMessageAttributed&& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Object to Copy From</param>
		/// <returns>Newly Created Object</returns>
		EventMessageAttributed& operator=(const EventMessageAttributed& other) = default;

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">Object to Move From</param>
		/// <returns>Newly Created Object</returns>
		EventMessageAttributed& operator=(EventMessageAttributed&& other) = default;

		~EventMessageAttributed() = default;



	private:
		/// <summary>
		/// Subtype to accept events from
		/// </summary>
		std::string _subtype;

		/// <summary>
		/// Datum Signatures
		/// </summary>
		/// <returns>Prescribed Attribute Signatures</returns>
		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};
}
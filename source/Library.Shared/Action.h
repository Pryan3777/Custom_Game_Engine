#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "Attributed.h"
#include "GameClock.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Abstract class for Actions
	/// </summary>
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="type">Type for Child Creation</param>
		Action(RTTI::IdType type = TypeIdClass());

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Actoin to Copy From</param>
		Action(const Action& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Action to Copy From</param>
		/// <returns>Newly Created Action</returns>
		Action& operator=(const Action& other) = default;

		/// <summary>
		/// Name of this Action
		/// </summary>
		std::string _name;

		/// <summary>
		/// Updates this Action
		/// </summary>
		/// <param name="time">Current Game Time</param>
		virtual void Update(GameTime time) = 0;

		/// <summary>
		/// Signatures of Datums for this Object
		/// </summary>
		/// <returns>Vector of Signatures</returns>
		static Vector<Signature> Signatures();
	};
}
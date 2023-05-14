#pragma once

#include "ActionList.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Action to Increment or Decrement a Datum By Value
	/// </summary>
	class ActionIncrement : public ActionList
	{
		RTTI_DECLARATIONS(ActionIncrement, ActionList);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="type">Type for Child Creation</param>
		ActionIncrement(RTTI::IdType type = TypeIdClass());

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Actoin to Copy From</param>
		ActionIncrement(const ActionIncrement& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Action to Copy From</param>
		/// <returns>Newly Created Action</returns>
		ActionIncrement& operator=(const ActionIncrement& other) = default;

		/// <summary>
		/// Updates this Action
		/// </summary>
		/// <param name="time">Current Game Time</param>
		virtual void Update(GameTime time) override;

		/// <summary>
		/// Target to Increment
		/// Searches up Hierarchy
		/// </summary>
		std::string _target = "";

		/// <summary>
		/// Value to Increment By
		/// Negative Decrements
		/// </summary>
		int _value = 1;

		/// <summary>
		/// Index to affect in Datum
		/// </summary>
		int _index = 0;

		/// <summary>
		/// Create a Dynamically Allocated Copy of this Action
		/// </summary>
		/// <returns>Heap Allocated Copy of this Action</returns>
		Scope* Clone() override;

		/// <summary>
		/// Returns True if two Actoins are Equal
		/// </summary>
		/// <param name="rhs">Other Action to Compare</param>
		/// <returns>True if two Actoins are Equal</returns>
		bool Equals(const RTTI* rhs) const;

		/// <summary>
		/// Converts this Action to String
		/// </summary>
		/// <returns>String</returns>
		std::string ToString() const override;

		/// <summary>
		/// Signatures of Datums for this Object
		/// </summary>
		/// <returns>Vector of Signatures</returns>
		static Vector<Signature> Signatures();
	};
}

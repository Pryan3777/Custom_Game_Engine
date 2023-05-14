#pragma once

#include "ActionList.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Action to Increment or Decrement a Datum By Value
	/// </summary>
	class ActionIf : public ActionList
	{
		RTTI_DECLARATIONS(ActionIf, ActionList);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="type">Type for Child Creation</param>
		ActionIf(RTTI::IdType type = TypeIdClass());

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Actoin to Copy From</param>
		ActionIf(const ActionIf& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Action to Copy From</param>
		/// <returns>Newly Created Action</returns>
		ActionIf& operator=(const ActionIf& other) = default;

		/// <summary>
		/// Updates this Action
		/// </summary>
		/// <param name="time">Current Game Time</param>
		virtual void Update(GameTime time) override;

		/// <summary>
		/// Condition, 0 = true;
		/// </summary>
		int _condition = 0;

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

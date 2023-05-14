#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Inherits from ActionList and EventSubscriber
	/// </summary>
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="type">type</param>
		Reaction(RTTI::IdType type = TypeIdClass());
	};
}
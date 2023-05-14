#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "RTTI.h"
#include "Attributed.h"
#include "Signature.h"
#include "Scope.h"
#include "GameClock.h"
#include "GameTime.h"
#include "Action.h"

namespace FieaGameEngine
{
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed);

	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="type">Type Name</param>
		GameObject(RTTI::IdType type = TypeIdClass());

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"></param>
		GameObject(const GameObject& other) = default;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Game Object to Copy from</param>
		/// <returns>Copied Game Object</returns>
		GameObject& operator=(const GameObject& other) = default;

		/// <summary>
		/// Name of Game Object
		/// </summary>
		std::string _name;

		/// <summary>
		/// Position of Game Object
		/// </summary>
		glm::vec4 _position;

		/// <summary>
		/// Rotation of Game Object
		/// </summary>
		glm::vec4 _rotation;

		/// <summary>
		/// Scale of Game Object
		/// </summary>
		glm::vec4 _scale;

		/// <summary>
		/// Updates both this object, and children
		/// </summary>
		/// <param name="time">Current Game Time</param>
		void Update(GameTime time);
	protected:
		/// <summary>
		/// Update Method for this given Object. Overwrittable by Derived
		/// </summary>
		/// <param name="time">Current Game Time</param>
		virtual void UpdateLocal(GameTime time);

		/// <summary>
		/// Calss Updates on all GameObject Children
		/// </summary>
		/// <param name="time">Current Game Time</param>
		void UpdateChildren(GameTime time);
		
	public:
		/// <summary>
		/// Clones Given Game Object
		/// </summary>
		/// <returns>Copy of this Game Object</returns>
		Scope* Clone() override;

		/// <summary>
		/// Determines if two Game Objects are Equal
		/// </summary>
		/// <param name="rhs">Other Game Object to Compare</param>
		/// <returns>True if Objects are Equal</returns>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Converts this Game Object to String
		/// </summary>
		/// <returns>Stringified Game Object</returns>
		std::string ToString() const override;


		/// <summary>
		///	Returns Signatures for Presecribed Attributes
		/// </summary>
		/// <returns>Signatures for Presecribed Attributes</returns>
		static Vector<Signature> Signatures();
	};
}
#pragma once

#include "Scope.h"
#include "Signature.h"
#include "RTTI.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Scope with Prescribed Attributes
	/// </summary>
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	protected:
		/// <summary>
		/// Default Constructor, requires type of Attributed being created
		/// </summary>
		/// <param name="type">Type of Attributed being created</param>
		Attributed(size_t type);

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Attributed to Copy</param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">Attribtued to Move</param>
		Attributed(Attributed&& other) noexcept;

		/// <summary>
		/// Assignment Operaotr
		/// </summary>
		/// <param name="other">Attribtued to Copy</param>
		/// <returns>Copied Attributed</returns>
		Attributed& operator=(const Attributed& other);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">Attributed to Move</param>
		/// <returns>Moved Attributed</returns>
		Attributed& operator=(Attributed&& other) noexcept;

		/// <summary>
		/// Destructor for Attributed
		/// </summary>
		virtual ~Attributed() = default;
	
	public:
		/// <summary>
		/// Determins if a given string is an Attribute
		/// </summary>
		/// <param name="target">String to Check</param>
		/// <returns>True if String is an attribute</returns>
		bool IsAttribute(std::string target);

		/// <summary>
		/// Determins if a given string is a Prescribed Attribute
		/// </summary>
		/// <param name="target">String to Check</param>
		/// <returns>True if String is a prescribed attribute</returns>
		bool IsPrescribedAttribute(std::string target);

		/// <summary>
		/// Determins if a given string is an Auxiliary Attribute
		/// </summary>
		/// <param name="target">String to Check</param>
		/// <returns>True if String is an Auxiliary attribute</returns>
		bool IsAuxiliaryAttribute(std::string target);

		/// <summary>
		/// Gets Indexes of Attributes
		/// User Can then Get Attributes by Index
		/// Indexes are (,]
		/// </summary>
		/// <returns>Indexes of Range of Attribtutes</returns>
		std::pair<size_t, size_t> Attributes();

		/// <summary>
		/// Gets Indexes of Prescribed Attributes
		/// User Can then Get Attributes by Index
		/// Indexes are (,]
		/// </summary>
		/// <returns>Indexes of Range of Prescribed Attribtutes</returns>
		std::pair<size_t, size_t> PrescribedAttributes();

		/// <summary>
		/// Gets Indexes of Auxiliary Attributes
		/// User Can then Get Attributes by Index
		/// Indexes are (,]
		/// </summary>
		/// <returns>Indexes of Range of Auxiliary Attribtutes</returns>
		std::pair<size_t, size_t> AuxiliaryAttributes();

		/// <summary>
		/// Vector of Signatures to feed to Type Manager
		/// </summary>
		/// <returns>Vector of Signatures</returns>
		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	
	private:
		/// <summary>
		/// Populates Attributed with Prescribed Attributes
		/// </summary>
		/// <param name="type">Type to request from Type Manager</param>
		void Populate(size_t type);

		/// <summary>
		/// Index of Last Prescribed Attribute
		/// </summary>
		size_t _lastPrescribed = 1;
	};
}

#pragma once

#include <cstdint>
#include <stdexcept>
#include <functional>
#include <cstddef>
#include <string>
#include <glm/glm.hpp>
#include "RTTI.h"

#include "HashMap.h"
#include "Vector.h"
#include "Datum.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Scope that also Functions as a Table
	/// Inherits from RTTI
	/// </summary>
	class Scope : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Scope, FieaGameEngine::RTTI);

	public:
		/// <summary>
		/// Returns true if two RTTI are equal
		/// </summary>
		/// <param name="rhs">Value to Compare</param>
		/// <returns>true if RTTI are equivalent</returns>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="bins">Number of Bins for Hash map</param>
		Scope(size_t bins = 1);

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">Scope to Copy from</param>
		Scope(const Scope& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">Scope to Move from</param>
		Scope(Scope&& other) noexcept;

		/// <summary>
		/// Assignment Operator
		/// </summary>
		/// <param name="other">Scope to copy from</param>
		/// <returns>New Scope</returns>
		Scope& operator=(const Scope& other);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">Scope to Move From</param>
		/// <returns>New Scope</returns>
		Scope& operator=(Scope&& other) noexcept;

		/// <summary>
		/// Scope Destructor
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// Size of Scope
		/// </summary>
		/// <returns>Size of Scope</returns>
		size_t Size() const;

		/// <summary>
		/// Checks if scope is empty
		/// </summary>
		/// <returns>True if Scope Size is 0</returns>
		bool IsEmpty();

		/// <summary>
		/// Finds String in current scope only
		/// </summary>
		/// <param name="target">Name of thing to look for</param>
		/// <returns>Value associated with that name</returns>
		Datum* Find(const std::string target);

		/// <summary>
		/// Finds String in current scope only
		/// </summary>
		/// <param name="target">Name of thing to look for</param>
		/// <returns>Value associated with that name</returns>
		const Datum* Find(const std::string target) const;

		/// <summary>
		/// Propogates upwards, checking scopes for value
		/// </summary>
		/// <param name="target">Value to find</param>
		/// <param name="scopeOut">Output Parameter of Scope found in</param>
		/// <returns>Value associated with key</returns>
		Datum* Search(const std::string target, Scope** scopeOut = nullptr);

		/// <summary>
		/// Adds Datum to Scope with name Target
		/// </summary>
		/// <param name="target">Name of new Datum</param>
		/// <returns>Value of Created or found Datum</returns>
		Datum& Append(const std::string target);

		/// <summary>
		/// Adds a Scope under this one, creating a Datum if needed
		/// </summary>
		/// <param name="target">Name of Datum scope is or will be in</param>
		/// <returns>New Scope</returns>
		Scope& AppendScope(const std::string target);

		/// <summary>
		/// Adopts child, orphaning if necessary
		/// </summary>
		/// <param name="child">Child to Adopt</param>
		/// <param name="name">Name to hold Child under</param>
		void Adopt(Scope& child, std::string name);

		/// <summary>
		/// Gets parent of Scope
		/// </summary>
		/// <returns>Scope Parent</returns>
		Scope* GetParent();

		/// <summary>
		/// Returns data with given name in current scope
		/// </summary>
		/// <param name="target">Name of data</param>
		/// <returns>Data to return</returns>
		Datum& operator[](const std::string target);

		/// <summary>
		/// Returns data at curretn index in curretn scope
		/// </summary>
		/// <param name="target">Index of Data</param>
		/// <returns>Data found or Created</returns>
		Datum& operator[](const size_t target);

		/// <summary>
		/// Checks if two Scopes are Equivalent
		/// </summary>
		/// <param name="other">Other scope to compare to</param>
		/// <returns>True if equivalent</returns>
		bool operator==(const Scope& other) const;

		/// <summary>
		/// Checks if two Scopes are Not Equivalent
		/// </summary>
		/// <param name="other">Other scope to compare to</param>
		/// <returns>False if equivalent</returns>
		bool operator!=(const Scope& other) const;

		/// <summary>
		/// Finds the datum and index in that datum of a given scope
		/// </summary>
		/// <param name="target">Scope to look for</param>
		/// <returns>Datum and Index in that Datum that the scope was found</returns>
		std::pair<Datum*, size_t> FindContainedScope(const Scope& target);

		/// <summary>
		/// Empties the Scope
		/// </summary>
		void Clear();

		/// <summary>
		/// Orphans current scope
		/// </summary>
		/// <returns> This Scope </returns>
		Scope* Orphan();

		/// <summary>
		/// Allocates a new scope that copies this one
		/// </summary>
		/// <returns>New Heap Allocated Scope</returns>
		virtual Scope* Clone();


		std::string FindName(size_t i)
		{
			return _index[i]->first;
		}

	protected:
		/// <summary>
		/// Finds index of Datum
		/// </summary>
		/// <param name="target">Datum to Find</param>
		/// <returns>Index of Datum</returns>
		size_t FindIndex(std::string target)
		{
			size_t i = 0;
			for (i; i < _index.Size(); ++i)
			{
				if (_index[i]->first == target)
				{
					break;
				}
			}
			return i;
		}

	protected:
		/// <summary>
		/// Recursive helper function for search
		/// </summary>
		/// <param name="target">Value to look for</param>
		/// <param name="scopeOut">Output Parameter of scope found in</param>
		/// <param name="scope">Current Scope to search in</param>
		/// <returns>Found Value</returns>
		Datum* SearchR(const std::string target, Scope** scopeOut, Scope* scope);

		/// <summary>
		/// Holds order of Hash Map
		/// </summary>
		Vector<std::pair<const std::string, Datum>*> _index;

		/// <summary>
		/// Holds Datum in Scope with assosciated names as strings
		/// </summary>
		HashMap<const std::string, Datum> _data;

		/// <summary>
		/// Parent of this scope, nullptr if none
		/// </summary>
		Scope* _parent = nullptr;

		/// <summary>
		/// Number of bins for hashmap
		/// </summary>
		size_t _bins = 1;
	};
}
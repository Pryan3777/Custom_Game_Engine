#pragma once
#include <string>
#include <stddef.h>

#include "Datum.h"
#include "Scope.h"
namespace FieaGameEngine
{
	/// <summary>
	/// Signature Describing a Prescribed Datum
	/// </summary>
	class Signature
	{
	public:
		/// <summary>
		/// Constructor for a Signature
		/// </summary>
		/// <param name="name">Name of Datum</param>
		/// <param name="type">Type of Datum</param>
		/// <param name="size">Numbr of Datums</param>
		/// <param name="offset">Positoin of Data for External Storage</param>
		Signature(std::string name, Datum::DatumTypes type, size_t size = 1, size_t offset = 0);
		
		/// <summary>
		/// Creates an instance of this datum
		/// </summary>
		/// <param name="s">Scope to add created datum to</param>
		void Populate(Scope* s);

	private:
		/// <summary>
		/// Name of Datum
		/// </summary>
		std::string _name;

		/// <summary>
		/// Type of Datum
		/// </summary>
		Datum::DatumTypes _type;

		/// <summary>
		/// Number of Datums
		/// </summary>
		size_t _size = 1;

		/// <summary>
		/// Position of Data for External Storage
		/// </summary>
		size_t _offset = 0;

		// SAVING THIS FOR NEXT ASSIGNMENT
		//static HashMap<std::string, Datum::DatumTypes> _stringToType;
	};
}
#pragma once

#include <HashMap.h>

namespace FieaGameEngine
{
	template <typename T>
	class Factory
	{
	public:
		/// <summary>
		/// Virtual Destructor since it is inheritable
		/// </summary>
		virtual ~Factory() = default;

		/// <summary>
		/// Finds given factory by name. Throws if not found
		/// </summary>
		/// <param name="name">Name of Product Factory Produces</param>
		/// <returns>Pointer to Factory</returns>
		static Factory* Find(const std::string &name);

		/// <summary>
		/// Creates a given Object by calling the appropriate factory. Throws if Factory not found
		/// </summary>
		/// <param name="name">Name of Product to Produce</param>
		/// <returns>Pointer to Produced Objected</returns>
		static T* Create(const std::string &name);

		/// <summary>
		/// Adds Factory to Root Factory, Called in Macro
		/// </summary>
		/// <param name="factory">Factory to Add</param>
		static void Add(Factory *factory);

		/// <summary>
		/// Removes and Deletes all Added Factories
		/// </summary>
		static void Clear();


		/// <summary>
		/// The individual Factory Produces one of its Products
		/// </summary>
		/// <returns>A pointer to a given Product</returns>
		virtual T* CreateProduct() = 0;

		/// <summary>
		/// Name of the Product Produced by this Factory
		/// </summary>
		/// <returns>Name of Product</returns>
		virtual const std::string ClassName() const = 0;

	private:
		/// <summary>
		/// Hash Map holding all Factories
		/// </summary>
		static inline HashMap<const std::string, Factory*> _factories{1};
	};
}

#include "Factory.inl"
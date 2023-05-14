#pragma once

#include "HashMap.h"
#include "Signature.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Singleton for holding Signature Vectors
	/// </summary>
	class TypeManager final
	{
	public:
		/// <summary>
		/// Gets created Instance of TypeManager
		/// Must Call CreateInstance first
		/// </summary>
		/// <returns></returns>
		static TypeManager* Instance()
		{
			return _instance;
		}

		/// <summary>
		/// Creates the Instance of TypeManager
		/// </summary>
		static void CreateInstance()
		{
			assert(_instance == nullptr);
			_instance = new TypeManager;
		}

		/// <summary>
		/// Deletes the instance of TypeManager
		/// </summary>
		static void DestroyInstance()
		{
			delete _instance;
			_instance = nullptr;
		}

		/// <summary>
		/// Adds a Vector of Signatures from an Object to the Type Manager
		/// </summary>
		/// <param name="type">RTTI Type that is being added</param>
		/// <param name="signatures">Signatures at the types direct level</param>
		/// <param name="parentType">Parent to copy their signatures</param>
		void Add(RTTI::IdType type, Vector<Signature> signatures, RTTI::IdType parentType);

		
		[[nodiscard]] 
		/// <summary>
		/// Gets Signatures for a given type
		/// </summary>
		/// <param name="typeId">Type to get signatures for</param>
		/// <returns>Vector of Signatures for a given type</returns>
		Vector<Signature>& GetSignaturesForTypeId(size_t typeId);

	private:
		/// <summary>
		/// Constructor held private to prevent direct instantiation
		/// </summary>
		TypeManager() = default;

		/// <summary>
		/// Destructor held private to prevent direct destruction
		/// </summary>
		~TypeManager() = default;

		/// <summary>
		/// No Copy Constructor Allowed
		/// </summary>
		/// <param name=""></param>
		TypeManager(const TypeManager&) = delete;

		/// <summary>
		/// No Copy Assignment Operator Allowed
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		TypeManager& operator=(const TypeManager&) = delete;

		/// <summary>
		/// Single Instance of TypeManager
		/// </summary>
		inline static TypeManager *_instance {nullptr};

		/// <summary>
		/// Hash Map storing Vectors of Signatures
		/// </summary>
		HashMap<const RTTI::IdType, Vector<Signature>> _signatures = {10};
	};

	/// <summary>
	/// Add a new Type to the Type Manager
	/// </summary>
	/// <typeparam name="Type">Type tp add</typeparam>
	/// <typeparam name="ParentType">Paretns Type</typeparam>
	template <typename Type, typename ParentType>
	void RegisterType()
	{
		TypeManager::Instance()->Add(Type::TypeIdClass(), Type::Signatures(), ParentType::TypeIdClass());
	}
}
#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <utility>

#include "DefaultHash.h"
#include "Vector.h"
#include "SList.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TData>
	/// <summary>
	/// Unordered Map
	/// </summary>
	/// <typeparam name="TData">Data Type to Store</typeparam>
	/// <typeparam name="TKey">Key Type to Access the Data</typeparam>
	class HashMap final
	{
	public:
		/// <summary>
		/// Iterator for Unordered Map
		/// </summary>
		class Iterator final
		{
			friend HashMap;
		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			Iterator() = default;
		private:
			/// <summary>
			/// Assign Iterator to Specific Map
			/// </summary>
			/// <param name="map">Map to Assign to</param>
			Iterator(HashMap& map);

			/// <summary>
			/// Copy Constructor
			/// </summary>
			/// <param name="other">Iterator to Copy</param>
			Iterator(const Iterator& other);
		public:
			/// <summary>
			/// Assignment Operator
			/// </summary>
			/// <param name="other">Iterator to Copy</param>
			/// <returns>Copied Iterator</returns>
			Iterator operator=(const Iterator& other);

			/// <summary>
			/// Move Assignment Operator
			/// </summary>
			/// <param name="other">Iteartor to Move From</param>
			/// <returns>Moved Iterator</returns>
			Iterator operator=(Iterator&& other);
			
			/// <summary>
			/// Prefix Increment Operator
			/// </summary>
			/// <returns>Value after Increment</returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix Increment Operator
			/// </summary>
			/// <param name=""></param>
			/// <returns>Value before Increment</returns>
			Iterator operator++(int);

			/// <summary>
			/// Derference Operator
			/// </summary>
			/// <returns>std::pair stored</returns>
			std::pair<const TKey, TData>& operator*() const;

			/// <summary>
			/// Arrow Operater
			/// </summary>
			/// <returns>std::pair stored</returns>
			std::pair<const TKey, TData>* operator->() const;

			/// <summary>
			/// Checks if Iterators are Equivalent
			/// </summary>
			/// <param name="other">Iterator to check against this</param>
			/// <returns>True if Iterators are Equal</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Checks if Iterators are Not Equivalent
			/// </summary>
			/// <param name="other">Iterator to check against this</param>
			/// <returns>True if Iterators are Not Equal</returns>
			bool operator!=(const Iterator& other) const;
		
		private:
			/// <summary>
			/// Associated hash Map
			/// </summary>
			HashMap* _container{nullptr};

			/// <summary>
			/// Vector Iterator
			/// </summary>
			typename Vector<SList<std::pair<const TKey, TData>>>::Iterator _vecIterator{ Vector<SList<std::pair<const TKey, TData>>>::Iterator() };
			
			/// <summary>
			/// SList Iterator
			/// </summary>
			typename SList<std::pair<const TKey, TData>>::Iterator _listIterator{ SList<std::pair<const TKey, TData>>::Iterator() };
		};

		/// <summary>
		/// ConstIterator for Unordered Map
		/// </summary>
		class ConstIterator final
		{
			friend HashMap;
		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Copies Iterator to Construct ConstIterator
			/// </summary>
			/// <param name="other">Iterator to Copy</param>
			ConstIterator(const Iterator& other);
		private:
			/// <summary>
			/// Assign Iterator to Specific Map
			/// </summary>
			/// <param name="map">Map to Assign to</param>
			ConstIterator(const HashMap& map);

			/// <summary>
			/// Copy Constructor
			/// </summary>
			/// <param name="other">ConstIterator to Copy</param>
			ConstIterator(const ConstIterator& other);
		public:
			/// <summary>
			/// Assignment Operator
			/// </summary>
			/// <param name="other">ConstIterator to Copy</param>
			/// <returns>Copied ConstIterator</returns>
			ConstIterator operator=(const ConstIterator& other);

			/// <summary>
			/// Move Assignment Operator
			/// </summary>
			/// <param name="other">ConstIteartor to Move From</param>
			/// <returns>Moved ConstIterator</returns>
			ConstIterator operator=(ConstIterator&& other);

			/// <summary>
			/// Prefix Increment Operator
			/// </summary>
			/// <returns>Value after Increment</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix Increment Operator
			/// </summary>
			/// <param name=""></param>
			/// <returns>Value before Increment</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Derference Operator
			/// </summary>
			/// <returns>std::pair stored</returns>
			const std::pair<const TKey, TData>& operator*() const;

			/// <summary>
			/// Arrow Operater
			/// </summary>
			/// <returns>std::pair stored</returns>
			const std::pair<const TKey, TData>* operator->();

			/// <summary>
			/// Checks if Iterators are Equivalent
			/// </summary>
			/// <param name="other">Iterator to check against this</param>
			/// <returns>True if Iterators are Equal</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Checks if Iterators are Not Equivalent
			/// </summary>
			/// <param name="other">Iterator to check against this</param>
			/// <returns>True if Iterators are Not Equal</returns>
			bool operator!=(const ConstIterator& other) const;
		private:

			/// <summary>
			/// Assosciated Hashmap
			/// </summary>
			const HashMap* _container{nullptr};

			/// <summary>
			/// Vector Iteraotr
			/// </summary>
			typename Vector<SList<std::pair<const TKey, TData>>>::ConstIterator _vecIterator{ Vector<SList<std::pair<const TKey, TData>>>::ConstIterator() };
			
			/// <summary>
			/// SList Iteartor
			/// </summary>
			typename SList<std::pair<const TKey, TData>>::ConstIterator _listIterator{ SList<std::pair<const TKey, TData>>::ConstIterator() };
		};

		friend ConstIterator;
		friend Iterator;
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="bins">Number of Bins</param>
		/// <param name="equalityFunctor">Equality Functor</param>
		/// <param name="hashFunctor">Hash Functor</param>
		HashMap(
			size_t bins,
			std::function<bool(const TKey&, const TKey&)> equalityFunctor = std::equal_to<TKey>(),
			std::function<size_t(const TKey)> hashFunctor = DefaultHash<TKey>()
		);

		HashMap(
			size_t bins,
			std::initializer_list<std::pair<const TKey, TData>> pairs,
			std::function<bool(const TKey&, const TKey&)> equalityFunctor = std::equal_to<TKey>(),
			std::function<size_t(const TKey)> hashFunctor = DefaultHash<TKey>()
		);

		/// <summary>
		/// Copy COnstructor
		/// </summary>
		/// <param name="other">Hash Map to Copy</param>
		HashMap(const HashMap& other);

		/// <summary>
		/// Move Construcot
		/// </summary>
		/// <param name="other">Hash Map to COpy</param>
		HashMap(HashMap&& other) noexcept;

		/// <summary>
		/// Assignment Operator
		/// </summary>
		/// <param name="other">Hash Map to Copy</param>
		/// <returns>Copied Value</returns>
		HashMap& operator=(const HashMap& other);

		/// <summary>
		/// MpoveAssignment Operator
		/// </summary>
		/// <param name="other">Hash Map to Copy</param>
		/// <returns>Copied Value</returns>
		HashMap& operator=(HashMap&& other) noexcept;

		/// <summary>
		/// Default Destructor
		/// </summary>
		virtual ~HashMap() = default;

		/// <summary>
		/// Find Value
		/// </summary>
		/// <param name="target">Valeu to Find</param>
		/// <returns>Iterator to Value</returns>
		Iterator Find(const TKey& target);

		/// <summary>
		/// Find Value
		/// </summary>
		/// <param name="target">Valeu to Find</param>
		/// <returns>Iterator to Value</returns>
		ConstIterator Find(const TKey& target) const;

		/// <summary>
		/// Insret Pair
		/// </summary>
		/// <param name="pair"> Pair to Insret</param>
		/// <returns>iterator to inserted</returns>
		Iterator Insert(const std::pair<const TKey, const TData>& pair);

		/// <summary>
		/// Finds value
		/// </summary>
		/// <param name="">value to find</param>
		/// <returns>reference to pair</returns>
		TData& operator[](const TKey);

		/// <summary>
		/// Removes value
		/// </summary>
		/// <param name="target">Value to remove</param>
		void Remove(const TKey target);

		/// <summary>
		/// Clears HashMap
		/// </summary>
		void Clear();

		/// <summary>
		/// Size of Hash Map
		/// </summary>
		/// <returns>Size of Hash Map</returns>
		size_t Size() const;

		/// <summary>
		/// Checks if Key is in hashmap
		/// </summary>
		/// <param name="target"> Key to look for</param>
		/// <returns>bool if key was found</returns>
		bool ContainsKey(const TKey target) const;

		/// <summary>
		/// Finds value at index
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		TData& At(const TKey target);


		const TData& At(const TKey target) const;

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to beginning</returns>
		Iterator begin();

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to end</returns>
		Iterator end();

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to beginning</returns>
		ConstIterator begin() const;

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to end</returns>
		ConstIterator end() const;

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to beginning</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// iterator to beginning
		/// </summary>
		/// <returns>iterator to end</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Allocated Vector
		/// </summary>
		void Allocate();

		/// <summary>
		/// Compares keys of pair
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		inline bool pairCompare(const std::pair<const TKey, TData>& a, const std::pair<const TKey, TData>& b);

	private:
		size_t _bins;
		Vector<SList<std::pair<const TKey, TData>>> _data{Vector<SList<std::pair<const TKey, TData>>>(_bins)};
		size_t _size{0};
		std::function<bool(const TKey&, const TKey&)> _equality;
		std::function<size_t(const TKey)> _hash;
	};

}

#include "HashMap.inl"
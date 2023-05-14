#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>

namespace FieaGameEngine
{
	template <typename T>
	class SList
	{


	private:
	
		struct Node
		{
			friend class Iterator;
			friend class ConstIterator;

			/// <summary>
			/// Value stored in Node
			/// </summary>
			T Data;
			/// <summary>
			/// Pointer to next Node
			/// </summary>
			Node* Next{ nullptr };

			/// <summary>
			/// Constructor for Node
			/// </summary>
			/// <param name="data">Data to store in node</param>
			/// <param name="next">Next Node</param>
			Node(const T& data, Node* next = nullptr);

			Node(T&& data, Node* next = nullptr);

		};
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = T&&;
		friend class Iterator;
		friend class ConstIterator;

		class Iterator final
		{
			friend SList;
			friend class ConstIterator;
		public:
			/// <summary>
			/// Default Constructor for Iterator
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Constructor for Iterator
			/// </summary>
			/// <param name="SList">SList to associate with Iterator</param>
			/// <param name="Node">Node to associate with Iterator</param>
			Iterator(const SList& list);

			/// <summary>
			/// Determines if two Iterators are NOT equivalent
			/// </summary>
			/// <param name="other">The other Iterator</param>
			/// <returns>Returns true if Iterators are NOT Equivalent</returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Determines if two Iterators are equivalent
			/// </summary>
			/// <param name="other">The other Iterator</param>
			/// <returns>Returns true if Iterators are Equivalent</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Dereferences the Iterator
			/// </summary>
			/// <returns>The value the Iterator points</returns>
			reference operator*() const;

			/// <summary>
			/// Prefix operator for Iterator
			/// </summary>
			/// <returns>Reference to Iterator after increment</returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix operator for Iterator
			/// Use Prefix when able
			/// </summary>
			/// <param name=""></param>
			/// <returns>Copy of Iterator before increment</returns>
			Iterator operator++(int);
		private:
			/// <summary>
			/// Node currently pointed at
			/// </summary>
			typename SList<T>::Node* _node { nullptr };
			/// <summary>
			/// List Iterator applies to
			/// </summary>
			const SList* _container{ nullptr };
		};

		class ConstIterator final
		{
			friend SList;
			friend Iterator;
		public:
			/// <summary>
			/// Default Constructor for ConstIterator
			/// </summary>
			ConstIterator() = default;


			/// <summary>
			/// Constructor for ConstIterator
			/// </summary>
			/// <param name="list">SList to associate with ConstIterator</param>
			/// <param name="node">Node to set as target</param>
			ConstIterator(const SList& list);

			/// <summary>
			/// Uses an Iterator to create an equivalent ConstIterator
			/// </summary>
			/// <param name="other">Iterator to copy</param>
			ConstIterator(const Iterator& other);

			/// <summary>
			/// Determines if two ConstIterators are NOT equivalent
			/// </summary>
			/// <param name="other">The other ConstIterator</param>
			/// <returns>Returns true if ConstIterators are NOT Equivalent</returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Determines if two ConstIterators are equivalent
			/// </summary>
			/// <param name="other">The other ConstIterator</param>
			/// <returns>Returns true if ConstIterators are Equivalent</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Dereferences the ConstIterator
			/// </summary>
			/// <returns>The value the ConstIterator points</returns>
			const_reference operator*() const;

			/// <summary>
			/// Prefix operator for ConstIterator
			/// </summary>
			/// <returns>Reference to ConstIterator after increment</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix operator for ConstIterator
			/// Use Prefix when able
			/// </summary>
			/// <param name=""></param>
			/// <returns>Copy of ConstIterator before increment</returns>
			ConstIterator operator++(int);
		private:
			/// <summary>
			/// List ConstIterator applies to
			/// </summary>
			const SList* _container{ nullptr };
			/// <summary>
			/// Node currently pointed at
			/// </summary>
			typename SList<T>::Node* _node{ nullptr };
		};

	public:
		friend Iterator;
		friend ConstIterator;

		/// <summary>
		/// Constructor for Empty SList
		/// </summary>
		SList() = default;

		/// <summary>
		/// Copy Constructor for SList
		/// </summary>
		/// <param name="rhs">SList to Copy</param>
		SList(const SList& rhs);

		SList(SList&& rhs) noexcept;

		/// <summary>
		/// Assignment Constructor for SList
		/// </summary>
		/// <param name="other">SList to Copy</param>
		/// <returns>Reference to new SList</returns>
		SList& operator=(const SList& other);

		SList& operator=(SList&& other) noexcept;

		/// <summary>
		/// Destructor for SList
		/// </summary>
		virtual ~SList();

		/// <summary>
		/// Gets Iterator to head of SList
		/// </summary>
		/// <returns>Iterator to head of SList</returns>
		Iterator begin();

		/// <summary>
		/// Gets Iterator to back of SList
		/// </summary>
		/// <returns>Iterator for SList with nullptr</returns>
		Iterator end();

		/// <summary>
		/// Gets ConstIterator to head of SList
		/// </summary>
		/// <returns>ConstIterator to head of SList</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Gets ConstIterator to back of SList
		/// </summary>
		/// <returns>ConstIterator for SList with nullptr</returns>
		ConstIterator end() const;

		/// <summary>
		/// Gets ConstIterator to head of SList
		/// </summary>
		/// <returns>ConstIterator to head of SList</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Gets ConstIterator to back of SList
		/// </summary>
		/// <returns>ConstIterator for SList with nullptr</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Inserts given element after position of Iterator
		/// </summary>
		/// <param name="">Iterator of Position to insert</param>
		/// <param name="">Data to Insert</param>
		void InsertAfter(Iterator, T);

		/// <summary>
		/// Inserts given element after position of ConsIterator
		/// </summary>
		/// <param name="">ConstIterator of Position to insert</param>
		/// <param name="">Data to Insert</param>
		void InsertAfter(ConstIterator, T);

		/// <summary>
		/// Gets Iterator to Data in SList
		/// </summary>
		/// <param name="">Data to find</param>
		/// <returns>Iterator to Data or EOL</returns>
		Iterator Find(const T&, std::function<bool(const T&, const T&)> eq = std::equal_to<T>());

		/// <summary>
		/// Gets ConstIterator to Data in SList
		/// </summary>
		/// <param name="">Data to find</param>
		/// <returns>ConstIterator to Data or EOL</returns>
		ConstIterator Find(const T&, std::function<bool(const T&, const T&)> eq = std::equal_to<T>()) const;

		/// <summary>
		/// Attempts to Remove Data in SList
		/// </summary>
		/// <param name="">Data to Remove</param>
		/// <returns>Whether or not the data was removed</returns>
		bool Remove(const T&);

		/// <summary>
		/// Attempts to Remove Data in SList
		/// </summary>
		/// <param name="">Data to Remove</param>
		/// <returns>Whether or not the data was removed</returns>
		bool Remove(Iterator);

		
		[[nodiscard]] 
		/// <summary>
		/// Returns the size of the SList
		/// </summary>
		/// <returns></returns>
		size_t Size() const;

		[[nodiscard]] 
		/// <summary>
		/// Returns the head of the SList
		/// </summary>
		/// <returns>Data in first node of list</returns>
		T& Front();
		
		[[nodiscard]] 
		/// <summary>
		/// Returns the head of the SList
		/// </summary>
		/// <returns>Data in first node of list</returns>
		const T& Front() const;

		[[nodiscard]] 
		/// <summary>
		/// Returns the last value of the SList
		/// </summary>
		/// <returns>Data in last node of list</returns>
		T& Back();

		[[nodiscard]] 
		/// <summary>
		/// Returns the last of the SList
		/// </summary>
		/// <returns>Data in last node of list</returns>
		const T& Back() const;

		/// <summary>
		/// Deletes all Nodes in SList
		/// </summary>
		void Clear();

		/// <summary>
		/// Adds Data to front of SList
		/// </summary>
		/// <param name="value">Data to add to front of SList</param>
		void PushFront(const T& value);

		/// <summary>
		/// Adds Data to back of SList
		/// </summary>
		/// <param name="value">Data to add to back of SList</param>
		void PushBack(const T& value);

		/// <summary>
		/// Deletes first Node in SList and returns its data
		/// </summary>
		/// <returns>Data of deleted Node</returns>
		T PopFront();

		/// <summary>
		/// Deletes last Node in SList and returns its data
		/// </summary>
		/// <returns>Data of deleted Node</returns>
		T PopBack();

		[[nodiscard]] 
		/// <summary>
		/// Checks if SList has no Nodes
		/// </summary>
		/// <returns>True if SList has no Nodes</returns>
		bool IsEmpty() const;

	private:
		/// <summary>
		/// Pointer to first Node in SList
		/// </summary>
		Node* _front{ nullptr };

		/// <summary>
		/// Pointer to last Node in SList
		/// </summary>
		Node* _back{ nullptr };

		/// <summary>
		/// Number of Nodes in SList
		/// </summary>
		std::size_t _size{ 0 };
	};
}

#include "SList.inl"
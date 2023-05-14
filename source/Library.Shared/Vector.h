#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
namespace FieaGameEngine
{
	template <typename T>
	class Vector
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = T&&;

		class Iterator final
		{
			friend Vector;
		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			Iterator();

			/// <summary>
			/// Creates Iterator to Specific Vector at Node
			/// </summary>
			/// <param name="">Target Vector</param>
			/// <param name="">Target Node</param>
			Iterator(Vector&, size_t = 0);

			/// <summary>
			/// Copy Constructor for Iterator
			/// </summary>
			/// <param name="">Iterator to Copy</param>
			Iterator(const Iterator&);

			/// <summary>
			/// Copy Assignment Operator
			/// </summary>
			/// <param name="">Iterator to Copy</param>
			/// <returns>Copied Iterator</returns>
			Iterator operator=(const Iterator&);

			/// <summary>
			/// Checks if two Iterators are equivalent
			/// </summary>
			/// <param name="other">Other Iterator</param>
			/// <returns>Whether Iterators are Equal</returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Checks if two Iterators are NOT equivalent
			/// </summary>
			/// <param name="other">Other Iterator</param>
			/// <returns>Whether Iterators are NOT Equivalent</returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Prefix Increment for Iterator
			/// </summary>
			/// <returns>Value after Increment</returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix Incrememnt for Iterator
			/// </summary>
			/// <param name=""></param>
			/// <returns>Value before Increment</returns>
			Iterator operator++(int);

			/// <summary>
			/// Prefix Decrement for Iterator
			/// </summary>
			/// <returns>Value after Decrement</returns>
			Iterator& operator--();

			/// <summary>
			/// Postfix Decrememnt for Iterator
			/// </summary>
			/// <param name=""></param>
			/// <returns>Value before Decrement</returns>
			Iterator operator--(int);

			/// <summary>
			/// Dereference Operator for Iterator
			/// </summary>
			/// <returns>Value Iterator points at</returns>
			reference operator*() const;

			/// <summary>
			/// Dereference Operator for Iterator
			/// </summary>
			/// <returns>Value Iterator points at</returns>
			T* operator->() const;

		private:
			/// <summary>
			/// Vector Iterator refers to.
			/// </summary>
			Vector* _container { nullptr };

			/// <summary>
			/// Node Iterator refers to.
			/// </summary>
			size_type _node { 0 };
		};

		class ConstIterator final
		{
			friend Vector;

		public:
			/// <summary>
			/// Default Constructor
			/// </summary>
			ConstIterator();

			/// <summary>
			/// Creates ConstIterator to Specific Vector at Node
			/// </summary>
			/// <param name="">Target Vector</param>
			/// <param name="">Target Node</param>
			ConstIterator(const Vector&, size_type = 0);

			/// <summary>
			/// Copy Constructor for ConstIterator
			/// </summary>
			/// <param name="">ConstIterator to Copy</param>
			ConstIterator(const ConstIterator&);

			/// <summary>
			/// Copies Iterator to ConstIterator
			/// </summary>
			/// <param name="">Iterator to Copy</param>
			ConstIterator(const Iterator&);

			/// <summary>
			/// Copy Assignment Operator
			/// </summary>
			/// <param name="">ConstIterator to Copy</param>
			/// <returns>Copied ConstIterator</returns>
			ConstIterator operator=(const ConstIterator&);

			/// <summary>
			/// Checks if two ConstIterators are equivalent
			/// </summary>
			/// <param name="other">Other ConstIterator</param>
			/// <returns>Whether ConstIterators are Equal</returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Checks if two Iterators are NOT equivalent
			/// </summary>
			/// <param name="other">Other Iterator</param>
			/// <returns>Whether Iterators are NOT Equal</returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Prefix Increment for ConstIterator
			/// </summary>
			/// <returns>Value after Increment</returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix Increment for ConstIterator
			/// </summary>
			/// <returns>Value before Increment</returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Prefix Decrement for ConstIterator
			/// </summary>
			/// <returns>Value after Decrement</returns>
			ConstIterator& operator--();

			/// <summary>
			/// Postfix Decrement for ConstIterator
			/// </summary>
			/// <returns>Value before Decrement</returns>
			ConstIterator operator--(int);

			/// <summary>
			/// Dereference Operator for Iterator
			/// </summary>
			/// <returns>Value Iterator points at</returns>
			const_reference operator*() const;

			/// <summary>
			/// Dereference Operator for Iterator
			/// </summary>
			/// <returns>Value Iterator points at</returns>
			const T* operator->() const;

		private:
			/// <summary>
			/// Vector ConstIterator refers to
			/// </summary>
			const Vector* _container{ nullptr };

			/// <summary>
			/// Node ConstIterator refers to
			/// </summary>
			size_type _node{ 0 };
		};
		/// <summary>
		/// Default Constructor for Vector
		/// </summary>
		Vector();

		/// <summary>
		/// Constructs Vector with specified Capacity
		/// </summary>
		/// <param name="capacity">Initial Capacity of Vector</param>
		Vector(size_type capacity);

		Vector(std::initializer_list<T> values);

		/// <summary>
		/// Copy Constructor for Vector
		/// </summary>
		/// <param name="other">Vector to Copy</param>
		Vector(const Vector& other);

		/// <summary>
		/// Move Constructor for Vector
		/// </summary>
		/// <param name="other">Vector to move Data from</param>
		Vector(Vector&& other) noexcept;

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Vector to Copy</param>
		/// <returns>New Vector Copied</returns>
		Vector& operator=(const Vector& other);

		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="">Vector to move Data from</param>
		/// <returns>New Vector Created</returns>
		Vector& operator=(Vector&&) noexcept;

		/// <summary>
		/// Vector Destructor
		/// </summary>
		virtual ~Vector();

		[[nodiscard]] 
		/// <summary>
		/// Gets element at specified index
		/// </summary>
		/// <param name="">Index to retrieve</param>
		/// <returns>Value at given Index</returns>
		reference operator[](size_type);

		[[nodiscard]] 
		/// <summary>
		/// Gets const element at specified index
		/// </summary>
		/// <param name="">Index to retrieve</param>
		/// <returns>Const Value at given Index</returns>
		const_reference operator[](size_type) const;

		/// <summary>
		/// Adds value to back of Vector. Increases Capacity as Needed.
		/// </summary>
		/// <param name="">Value to add to Vector</param>
		void PushBack(const T&);
		void push_back(const T&);

		[[nodiscard]] 
		/// <summary>
		/// Gets element at specified index
		/// </summary>
		/// <param name="">Index to retrieve</param>
		/// <returns>Value at given Index</returns>
		reference At(size_type);

		[[nodiscard]] 
		/// <summary>
		/// Gets const element at specified index
		/// </summary>
		/// <param name="">Index to retrieve</param>
		/// <returns>Const Value at given Index</returns>
		const_reference At(size_type) const;

		/// <summary>
		/// Removes element at Back of Vector
		/// </summary>
		void PopBack();
		void pop_back();

		[[nodiscard]] 
		/// <summary>
		/// Checks whether Vector is Empty or not
		/// </summary>
		/// <returns>True if Vector is Empty</returns>
		bool IsEmpty();

		[[nodiscard]] 
		/// <summary>
		/// Gets first Element in Vector
		/// </summary>
		/// <returns>Reference to First Element in Vector</returns>
		reference Front();

		[[nodiscard]] 
		/// <summary>
		/// Gets Const first Element in Vector
		/// </summary>
		/// <returns>Const Reference to First Element in Vector</returns>
		const_reference Front() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets last Element in Vector
		/// </summary>
		/// <returns>Reference to Last Element in Vector</returns>
		reference Back();
		reference back();

		[[nodiscard]] 
		/// <summary>
		/// Gets Const last Element in Vector
		/// </summary>
		/// <returns>Const Reference to Last Element in Vector</returns>
		const_reference Back() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets Size of Vector
		/// </summary>
		/// <returns>Size of Vector</returns>
		const size_type Size() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets Capacity of Vector
		/// </summary>
		/// <returns>Capacity of Vector</returns>
		size_type Capacity() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets Iterator to Front of Vector
		/// </summary>
		/// <returns>Iterator to Front of Vector</returns>
		Iterator begin();

		[[nodiscard]] 
		/// <summary>
		/// Gets Iterator to Back of Vector
		/// </summary>
		/// <returns>Iterator to Back of Vector</returns>
		Iterator end();

		[[nodiscard]] 
		/// <summary>
		/// Gets ConstIterator to Front of Vector
		/// </summary>
		/// <returns>ConstIterator to Front of Vector</returns>
		ConstIterator begin() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets ConstIterator to Back of Vector
		/// </summary>
		/// <returns>ConstIterator to Back of Vector</returns>
		ConstIterator end() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets ConstIterator to Front of Vector
		/// </summary>
		/// <returns>ConstIterator to Front of Vector</returns>
		ConstIterator cbegin() const;

		[[nodiscard]] 
		/// <summary>
		/// Gets ConstIterator to Back of Vector
		/// </summary>
		/// <returns>ConstIterator to Back of Vector</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Reserves memory to set Capacity to specified value
		/// </summary>
		/// <param name="">Capacity to Reserve</param>
		void Reserve(size_type);

		[[nodiscard]] 
		/// <summary>
		/// Looks for Element in Vector
		/// </summary>
		/// <param name="">Element to find</param>
		/// <returns>Iterator to element or end of Vector if not found</returns>
		Iterator Find(const_reference);

		/// <summary>
		/// Destructs all elements and sets size to 0
		/// </summary>
		void Clear();

		/// <summary>
		/// Shrinks Capacity to Match Size
		/// </summary>
		void ShrinkToFit();

		/// <summary>
		/// Remove Element at given Iterator
		/// </summary>
		/// <param name="">Iterator to Remove at</param>
		void Remove(Iterator);

		/// <summary>
		/// Remove Element at given Index
		/// </summary>
		/// <param name="">Index to Remove at</param>
		void RemoveAt(size_t);
		

	private:
		/// <summary>
		/// Data Stored in Vector
		/// </summary>
		value_type* _data { nullptr };

		/// <summary>
		/// Current amount of Vector Storage in Use
		/// </summary>
		size_type _size { 0 };
		
		/// <summary>
		/// Total amount of Storage reserved by Vector Currently
		/// </summary>
		size_type _capacity { 0 };
	};
}

#include "Vector.inl"
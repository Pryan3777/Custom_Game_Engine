#include "Vector.h"

namespace FieaGameEngine
{
	template <typename T>
	inline Vector<T>::Vector()
	{
		
	}

	template<typename T>
	inline Vector<T>::Vector(size_type capacity)
	{
		Reserve(capacity);
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> values)
	{
		Reserve(values.size());
		for (const auto& value : values)
		{
			PushBack(value);
		}
	}

	template <typename T>
	inline Vector<T>::Vector(const Vector& other) :
		_size(other._size)
	{
		Reserve(other._capacity);
		for (size_t i = 0; i < _size; ++i)
		{
			new (_data + i) T(other[i]);
		}
	}

	template <typename T>
	inline Vector<T>::Vector(Vector&& other) noexcept :
		_size(other._size), _capacity(other._capacity), _data(std::move(other._data))
	{
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& other)
	{
		Clear();

		_size = other._size;
		Reserve(other._capacity);
		for (size_t i = 0; i < _size; ++i)
		{
			new (_data + i) T(other[i]);
		}
		return *this;
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
	{
		Clear();
		_size = other._size;
		_capacity = other._capacity;
		_data = std::move(other._data);
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
		return *this;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		ShrinkToFit();
	}

	template <typename T>
	T& Vector<T>::operator[](std::size_t index)
	{
		return At(index);
	}

	template <typename T>
	const T& Vector<T>::operator[](std::size_t index) const
	{
		return At(index);
	}

	template <typename T>
	void Vector<T>::PushBack(const T& value)
	{
		if (_size == _capacity)
		{
			Reserve(1 + _capacity + (_capacity / 2));
		}

		new (_data + _size) T(value);
		++_size;
	}

	template<typename T>
	void Vector<T>::push_back(const T& value)
	{
		PushBack(value);
	}

	template <typename T>
	T& Vector<T>::At(std::size_t index)
	{
		if (index >= _size)
		{
			throw std::runtime_error("Past end of Vector");
		}
		return _data[index];
	}

	template <typename T>
	const T& Vector<T>::At(std::size_t index) const
	{
		if (index >= _size)
		{
			throw std::runtime_error("Past end of Vector");
		}
		return _data[index];
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		Remove(--end());
	}

	template<typename T>
	inline void Vector<T>::pop_back()
	{
		PopBack();
	}

	template <typename T>
	bool Vector<T>::IsEmpty()
	{
		return _size == 0;
	}

	template <typename T>
	T& Vector<T>::Front()
	{
		return At(0);
	}

	template <typename T>
	const T& Vector<T>::Front() const
	{
		return At(0);
	}

	template <typename T>
	T& Vector<T>::Back()
	{
		return At((_size > 0 ? _size - 1 : 0));
	}

	template<typename T>
	T& Vector<T>::back()
	{
		return Back();
	}

	template <typename T>
	const T& Vector<T>::Back() const
	{
		return At(_size - 1);
	}

	template <typename T>
	const std::size_t Vector<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	std::size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator(*this);
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(*this, _size);
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return ConstIterator(*this);
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator(*this, _size);
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return ConstIterator(*this);
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return ConstIterator(*this, _size);
	}

	template <typename T>
	void Vector<T>::Reserve(size_t capacity)
	{
		if (capacity > _capacity)
		{
			T* data = reinterpret_cast<T*>(realloc(_data, capacity * sizeof(T)));
			_data = data;
			_capacity = capacity;
		}
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const_reference target)
	{
		Iterator i;
		for (i = begin(); i != end(); ++i)
		{
			if (*i == target)
				return i;
		}
		return i;
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		while (_size != 0)
		{
			PopBack();
		}
	}

	template <typename T>
	void Vector<T>::ShrinkToFit()
	{	
		if (_size == 0)
		{
			if (_capacity > 0 && _data != nullptr)
			{
				free(_data);
			}
		}
		else 
		{
			_data = reinterpret_cast<T*>(realloc(_data, _size * sizeof(T)));
			_capacity = _size;
		}
		return;
	}

	template <typename T>
	void Vector<T>::Remove(Iterator i)
	{
		if (i._container != this)
		{
			throw std::runtime_error("Invalid Iterator for Remove");
		}
		RemoveAt(i._node);
	}
	template <typename T>
	void Vector<T>::RemoveAt(size_t i)
	{
		if (i >= _size)
		{
			throw std::runtime_error("Invalid Index for Remove");
		}
		_data[i].~T();
		std::memmove(_data + i, _data + i + 1, sizeof(T) * (_size - i - 1));
		--_size;
	}
	


	
	template <typename T>
	inline Vector<T>::Iterator::Iterator()
	{
		
	}

	template <typename T>
	inline Vector<T>::Iterator::Iterator(Vector& other, size_t index) :
		_container(&other), _node(index)
	{
		
	}

	template <typename T>
	Vector<T>::Iterator::Iterator(const Iterator& other) :
		_container(other._container), _node(other._node)
	{
		
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator=(const Iterator& other)
	{
		_container = other._container;
		_node = other._node;
		return *this;
	}

	template <typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return _container == other._container && _node == other._node;
	}

	template <typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_node < _container->_size)
		{
			++_node;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		if (_node < _container->_size)
		{
			++_node;
		}
		return temp;
	}

	template <typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		if (_node > 0)
		{
			--_node;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator temp = *this;
		if (_node > 0)
		{
			--_node;
		}
		return *this;
	}

	template <typename T>
	typename T& Vector<T>::Iterator::operator*() const
	{
		return _container->At(_node);
	}

	template <typename T>
	typename T* Vector<T>::Iterator::operator->() const
	{
		return &(_container->At(_node));
	}


	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator()
	{

	}

	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector & other, size_t index) :
		_container(&other), _node(index)
	{

	}

	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const ConstIterator& other) :
		_container(other._container), _node(other._node)
	{

	}
	
	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _node(other._node)
	{

	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator=(const ConstIterator& other)
	{
		_container = other._container;
		_node = other._node;
		return *this;
	}

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return _container == other._container && _node == other._node;
	}

	template <typename T>
	inline bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template <typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_node < _container->_size)
		{
			++_node;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;
		if (_node < _container->_size)
		{
			++_node;
		}
		return temp;
	}

	template <typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--()
	{
		if (_node > 0)
		{
			--_node;
		}
		return *this;
	}

	template <typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		ConstIterator temp = *this;
		if (_node > 0)
		{
			--_node;
		}
		return *this;
	}

	template <typename T>
	typename const T& Vector<T>::ConstIterator::operator*() const
	{
		return _container->At(_node);
	}

	template <typename T>
	typename const T* Vector<T>::ConstIterator::operator->() const
	{
		return &(_container->At(_node));
	}
}
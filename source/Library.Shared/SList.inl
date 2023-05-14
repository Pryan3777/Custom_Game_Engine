#include "SList.h"
#include <functional>

namespace FieaGameEngine
{
	template <typename T>
	inline SList<T>::Node::Node(T&& data, Node* next) :
		Data{std::forward<T>(data)}, Next(next)
	{

	}


	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& list) :
		_container(&list), _node(list._front)
	{

	}

	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _node(other._node)
	{

	}

	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList& list) :
		_container(&list), _node(list._front)
	{
	}

	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return this->_container != other._container || this->_node != other._node;
	}

	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& other) const
	{
		return this->_container == other._container && this->_node == other._node;
	}

	template <typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Attempt to Dereference nullptr");
		}
		return this->_node->Data;
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Past end of list");
		}
		this->_node = this->_node->Next;
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Past end of list");
		}
		SList<T>::Iterator temp = *this;
		this->_node = this->_node->Next;
		return temp;
	}

	template <typename T>
	bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return this->_container != other._container || this->_node != other._node;
	}

	template <typename T>
	bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return this->_container == other._container && this->_node == other._node;
	}

	template <typename T>
	const T& SList<T>::ConstIterator::operator*() const
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Attempt to Dereference nullptr");
		}
		return this->_node->Data;
	}

	template <typename T>
	typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Past end of list");
		}
		this->_node = this->_node->Next;
		return *this;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int)
	{
		if (this->_node == nullptr)
		{
			throw std::runtime_error("Past end of list");
		}
		SList<T>::ConstIterator temp = *this;
		this->_node = this->_node->Next;
		return temp;
	}


	template<typename T>
	inline SList<T>::Node::Node(const T& data, Node* next) :
		Data(data), Next(next)
	{

	}

	/*template <typename T>
	inline SList<T>::SList(initializer_list<T> other)
	{
		for (const auto& value : other)
		{
			PushBack(value);
		}
	}*/

	template <typename T>
	SList<T>::SList(const SList& rhs)
	{
		Node* currentNode = rhs._front;
		while (currentNode != nullptr)
		{
			PushBack(currentNode->Data);
			currentNode = currentNode->Next;
		}
	}

	template<typename T>
	inline SList<T>::SList(SList&& other) noexcept : 
		_front(other._front), _back(other._back), _size(other._size)
	{
		other._size = 0;
		other._front = nullptr;
		other._back = nullptr;
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList& other)
	{
		if (this != &other)
		{
			Clear();

			Node* currentNode = other._front;
			while (currentNode != nullptr)
			{
				PushBack(currentNode->Data);
				currentNode = currentNode->Next;
			}
		}
		return *this;
	}

	template<typename T>
	inline SList<T>& SList<T>::operator=(SList&& other) noexcept
	{
		_front = other._front;
		_back = other._back;
		_size = other._size;

		other._front = nullptr;
		other._back = nullptr;
		other._size = 0;

		return *this;
	}

	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::begin()
	{
		Iterator it = Iterator(*this);
		it._node = this->_front;
		return it;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end()
	{
		Iterator it = Iterator(*this);
		it._node = nullptr;
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::begin() const
	{
		ConstIterator it = ConstIterator(*this);
		it._node = this->_front;
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::end() const
	{
		ConstIterator it = Iterator(*this);
		it._node = nullptr;
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::cbegin() const
	{
		ConstIterator it = ConstIterator(*this);
		it._node = this->_front;
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::cend() const
	{
		ConstIterator it = Iterator(*this);
		it._node = nullptr;
		return it;
	}

	template <typename T>
	void SList<T>::InsertAfter(SList<T>::Iterator it, T value)
	{
		if (it._container != this)
		{
			throw std::runtime_error("Iterator assigned to different list");
		}
		if (it._node == nullptr)
		{
			this->PushBack(value);
		}
		else if (it._node->Next == nullptr)
		{
			this->PushBack(value);
		}
		else
		{
			Node* node = new Node(value);
			node->Next = it._node->Next;
			it._node->Next = node;
			++this->_size;
		}
	}

	template <typename T>
	void SList<T>::InsertAfter(SList<T>::ConstIterator it, T value)
	{
		if (it._container != this)
		{
			throw std::runtime_error("Iterator assigned to different list");
		}
		if (it._node == nullptr)
		{
			this->PushBack(value);
		}
		else if (it._node->Next == nullptr)
		{
			this->PushBack(value);
		}
		else
		{
			Node* node = new Node(value);
			node->Next = it._node->Next;
			it._node->Next = node;
			++this->_size;
		}
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& target, std::function<bool(const T&, const T&)> eq)
	{
		Iterator it = this->begin();
		while (it._node != nullptr)
		{
			if (eq(* it, target))
			{
				break;
			}
			++it;
		}
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::Find(const T& target, std::function<bool(const T&, const T&)> eq) const
	{
		ConstIterator it = this->cbegin();
		while (it._node != nullptr)
		{
			if (eq(* it, target))
			{
				break;
			}
			++it;
		}
		return it;
	}

	template <typename T>
	bool SList<T>::Remove(Iterator it)
	{
		if (it._node == nullptr)
		{
			return false;
		}
		if (*it == this->Front())
		{
			it._node = it._node->Next;
			this->PopFront();
		}
		else
		{
			Node* before = this->_front;
			Node* itNode = it._node;
			while (before->Next != itNode)
			{
				before = before->Next;
			}
			before->Next = itNode->Next;
			delete(itNode);
			itNode = before->Next;
			--this->_size;
		}
		return true;
		// TODO
	}

	template <typename T>
	bool SList<T>::Remove(const T& target)
	{
		Iterator it = this->Find(target);
		if (it._node == nullptr)
		{
			return false;
		}
		if (*it == this->Front())
		{
			it._node = it._node->Next;
			this->PopFront();
		}
		else
		{
			Node* before = this->_front;
			Node* itNode = it._node;
			while (before->Next != itNode)
			{
				before = before->Next;
			}
			before->Next = itNode->Next;
			delete(itNode);
			itNode = before->Next;
			--this->_size;
		}
		return true;
		// TODO
	}

	template <typename T>
	inline size_t SList<T>::Size() const
	{
		return _size;
	}

	template<typename T>
	inline T& SList<T>::Front()
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		return _front->Data;
	}

	template<typename T>
	inline const T& SList<T>::Front() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		return _front->Data;
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		return _back->Data;
	}

	template<typename T>
	inline const T& SList<T>::Back() const
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		return _back->Data;
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while (_size > 0)
		{
			PopFront();
		}
	}

	template<typename T>
	void SList<T>::PushFront(const T& value)
	{
		Node* node = new Node(value);
		if (_size == 0)
		{
			_back = node;
		}
		else
		{
			node->Next = _front;
		}
		_front = node;
		_size++;
	}


	template<typename T>
	void SList<T>::PushBack(const T& value)
	{
		Node* node = new Node(value);
		if (_size == 0)
		{
			_front = node;
		}
		else
		{
			_back->Next = node;
		}
		_back = node;
		_size++;
	}

	template<typename T>
	T SList<T>::PopFront()
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		if (_size == 1)
		{
			_back = nullptr;
		}
		Node* target = _front;
		_front = _front->Next;
		T targetData = target->Data;
		delete(target);
		_size--;
		return targetData;
	}

	template<typename T>
	T SList<T>::PopBack()
	{
		if (_size == 0)
		{
			throw std::runtime_error("List is empty.");
		}
		if (_size == 1)
		{
			_front = nullptr;
			T targetData = _back->Data;
			delete(_back);
			_back = nullptr;
			_size--;
			return targetData;
		}
		Node* current = _front;
		while (current->Next != _back)
		{
			current = current->Next;
		}
		T targetData = _back->Data;
		delete(_back);
		_back = current;
		_size--;
		return targetData;
	}

	template<typename T>
	bool SList<T>::IsEmpty() const
	{
		return _size == 0;
	}
}
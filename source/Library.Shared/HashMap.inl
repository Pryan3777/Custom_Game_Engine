#include "HashMap.h"
#include "DefaultHash.h"

#include <cassert>

namespace FieaGameEngine
{
	template <typename TKey, typename TData>
	HashMap<TKey, TData>::Iterator::Iterator(HashMap& map) :
		_container(&map)
	{
		_vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator(_container->_data);
		while (_vecIterator != _container->_data.end() && (*_vecIterator).IsEmpty())
		{
			++_vecIterator;
		}
		if (_vecIterator != _container->_data.end())
		{
			_listIterator = (*_vecIterator).begin();
		}
	}

	template <typename TKey, typename TData>
	inline HashMap<TKey, TData>::Iterator::Iterator(const Iterator& other) :
		_container(other._container), _vecIterator(other._vecIterator), _listIterator(other._listIterator)
	{
		
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator=(const Iterator& other)
	{
		_container = other._container;
		_vecIterator = other._vecIterator;
		_listIterator = other._listIterator;
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator=(Iterator&& other)
	{
		_container = other._container;
		_vecIterator = other._vecIterator;
		_listIterator = other._listIterator;
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator& HashMap<TKey, TData>::Iterator::operator++()
	{
		if (_vecIterator != _container->_data.end())
		{
			++_listIterator;
			if (_listIterator == _vecIterator->end())
			{
				++_vecIterator;
				while (_vecIterator != _container->_data.end() && (*_vecIterator).IsEmpty())
				{
					++_vecIterator;
				}
				if (_vecIterator != _container->_data.end())
				{
					_listIterator = (*_vecIterator).begin();
				}
				else
				{
					_listIterator = SList<std::pair<TKey, TData>>::Iterator();
				}
			}
		}
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Iterator::operator++(int)
	{
		Iterator temp = *this;

		if (_vecIterator != _container->_data.end())
		{
			++_listIterator;
			if (_listIterator == _vecIterator->end())
			{
				++_vecIterator;
				while (_vecIterator != _container->_data.end() && (*_vecIterator).IsEmpty())
				{
					++_vecIterator;
				}
				if (_vecIterator != _container->_data.end())
				{
					_listIterator = (*_vecIterator).begin();
				}
				else
				{
					_listIterator = SList<std::pair<TKey, TData>>::Iterator();
				}
			}
		}

		return temp;
	}

	template <typename TKey, typename TData>
	inline std::pair<const TKey, TData>& HashMap<TKey, TData>::Iterator::operator*() const
	{
		if (*this == _container->end())
		{
			throw std::runtime_error("Past end of Map");
		}
		return *_listIterator;
	}

	template <typename TKey, typename TData>
	inline std::pair<const TKey, TData>* HashMap<TKey, TData>::Iterator::operator->() const
	{
		if (*this == _container->end())
		{
			throw std::runtime_error("Past end of Map");
		}
		return &(* _listIterator);
	}

	template <typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator==(const Iterator& other) const
	{
		return (_container == other._container && _listIterator == other._listIterator);
	}

	template <typename TKey, typename TData>
	bool HashMap<TKey, TData>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}


	template <typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const HashMap& map) :
		_container(&map)
	{
		_vecIterator = Vector<SList<std::pair<TKey, TData>>>::ConstIterator(_container->_data);
		while (_vecIterator != _container->_data.end() && (*_vecIterator).IsEmpty())
		{
			++_vecIterator;
		}
		if (_vecIterator != _container->_data.end())
		{
			_listIterator = (*_vecIterator).begin();
		}
	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const Iterator& other) :
		_container(other._container), _vecIterator(other._vecIterator), _listIterator(other._listIterator)
	{

	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>::ConstIterator::ConstIterator(const ConstIterator& other) :
		_container(other._container), _vecIterator(other._vecIterator), _listIterator(other._listIterator)
	{

	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator=(const ConstIterator& other)
	{
		_container = other._container;
		_vecIterator = other._vecIterator;
		_listIterator = other._listIterator;
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator=(ConstIterator&& other)
	{
		_container = other._container;
		_vecIterator = other._vecIterator;
		_listIterator = other._listIterator;
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator& HashMap<TKey, TData>::ConstIterator::operator++()
	{
		if (_vecIterator != _container->_data.cend())
		{
			++_listIterator;
			if (_listIterator == _vecIterator->cend())
			{
				++_vecIterator;
				while (_vecIterator != _container->_data.cend() && (*_vecIterator).IsEmpty())
				{
					++_vecIterator;
				}
				if (_vecIterator != _container->_data.cend())
				{
					_listIterator = (*_vecIterator).cbegin();
				}
				else
				{
					_listIterator = SList<std::pair<TKey, TData>>::ConstIterator();
				}
			}
		}
		return *this;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::ConstIterator::operator++(int)
	{
		ConstIterator temp = *this;

		if (_vecIterator != _container->_data.cend())
		{
			++_listIterator;
			if (_listIterator == _vecIterator->cend())
			{
				++_vecIterator;
				while (_vecIterator != _container->_data.cend() && (*_vecIterator).IsEmpty())
				{
					++_vecIterator;
				}
				if (_vecIterator != _container->_data.cend())
				{
					_listIterator = (*_vecIterator).cbegin();
				}
				else
				{
					_listIterator = SList<std::pair<TKey, TData>>::ConstIterator();
				}
			}
		}

		return temp;
	}

	template <typename TKey, typename TData>
	inline const std::pair<const TKey, TData>& HashMap<TKey, TData>::ConstIterator::operator*() const
	{
		if(*this == _container->end())
		{
			throw std::runtime_error("Past end of Map");
		}
		return *_listIterator;
	}

	template <typename TKey, typename TData>
	inline const std::pair<const TKey, TData>* HashMap<TKey, TData>::ConstIterator::operator->()
	{
		if (*this == _container->end())
		{
			throw std::runtime_error("Past end of Map");
		}
		return &(* _listIterator);
	}

	template <typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return (_container == other._container && _listIterator == other._listIterator);
	}

	template <typename TKey, typename TData>
	bool HashMap<TKey, TData>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}



	template <typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(size_t bins, std::function<bool(const TKey&, const TKey&)> equalityFunctor, std::function<size_t(const TKey)> hashFunctor) :
		_bins(bins), _equality(equalityFunctor), _hash(hashFunctor)
	{
		Allocate();
	}

	template<typename TKey, typename TData>
	inline HashMap<TKey, TData>::HashMap(size_t bins, std::initializer_list<std::pair<const TKey, TData>> pairs, std::function<bool(const TKey&, const TKey&)> equalityFunctor, std::function<size_t(const TKey)> hashFunctor) :
		_bins(bins), _equality(equalityFunctor), _hash(hashFunctor)
	{
		Allocate();

		for (const auto& pair : pairs)
		{
			Insert(pair);
		}
	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(const HashMap& other) :
		_bins(other._bins), _equality(other._equality), _hash(other._hash)
	{
		Allocate();
		
		ConstIterator it = other.cbegin();
		while (it != other.cend())
		{
			for (size_t i = 0; i < other._data.Size(); ++i)
			{
				SList<std::pair<TKey, TData>> a = other._data[i];
			}
			std::pair<TKey, TData> current = *it._listIterator;
			Insert(std::pair<TKey, TData>((*it._listIterator).first, (*it._listIterator).second));
			++it;
		}
	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>::HashMap(HashMap&& other) noexcept :
		_bins(other._bins), _data(std::move(other._data)), _size(other._size), _equality(other._equality), _hash(other._hash)
	{

	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>& HashMap<TKey, TData>::operator=(const HashMap& other)
	{
		Clear();
		_bins = other._bins;
		_equality = other._equality;
		_hash = other._hash;

		Allocate();

		ConstIterator it = other.begin();
		while (it != other.end())
		{
			Insert(std::pair<TKey, TData>(it->first, it->second));
			++it;
		}

		return *this;
	}

	template <typename TKey, typename TData>
	HashMap<TKey, TData>& HashMap<TKey, TData>::operator=(HashMap&& other) noexcept
	{
		Clear();
		_data.~Vector();
		_bins = other._bins;
		_data = std::move(other._data);
		_size = other._size;
		_equality = other._equality;
		_hash = other._hash;

		return *this;
	}


	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Find(const TKey& target)
	{
		Iterator it = Iterator(*this);
		size_t binIndex = _hash(target) % _bins;
		Vector<SList<std::pair<TKey, TData>>>& v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator::Iterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		auto end = it._vecIterator->end();
		while (it._listIterator != end && it->first != target)
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			it._vecIterator = _data.end();
			it._listIterator = SList<std::pair<TKey, TData>>::Iterator::Iterator();
		}
		return it;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::Find(const TKey& target) const
	{
		ConstIterator it = ConstIterator(*this);
		size_t binIndex = _hash(target) % _bins;
		const Vector<SList<std::pair<TKey, TData>>>& v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::ConstIterator::ConstIterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		auto end = it._vecIterator->end();
		while (it._listIterator != end && it->first != target)
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			it._vecIterator = _data.end();
			it._listIterator = SList<std::pair<TKey, TData>>::Iterator::Iterator();
		}
		return it;
	}


	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::Insert(const std::pair<const TKey, const TData>& pair)
	{
		bool created = false;
		Iterator it = Iterator(*this);
		size_t binIndex = _hash(pair.first) % _bins;
		Vector<SList<std::pair<TKey, TData>>> & v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator::Iterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		while (it._listIterator != it._vecIterator->end() && !pairCompare(*(it._listIterator), pair))
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			created = true;
			it._vecIterator->PushBack(pair);
			++_size;
			it._listIterator = it._vecIterator->begin();
			while (!pairCompare(*(it._listIterator), pair))
			{
				++it._listIterator;
			}
		}
		return it;
	}

	template <typename TKey, typename TData>
	TData& HashMap<TKey, TData>::operator[](const TKey target)
	{
		Iterator it = Iterator(*this);
		size_t binIndex = _hash(target) % _bins;
		Vector<SList<std::pair<TKey, TData>>>& v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator::Iterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		while (it._listIterator != it._vecIterator->end() && !_equality((*(it._listIterator)).first, target))
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			std::pair<TKey, TData> a = std::make_pair(target, TData());
			it = Insert(a);
		}
		return ((* it._listIterator).second);
	}

	template <typename TKey, typename TData>
	void HashMap<TKey, TData>::Remove(TKey target)
	{
		size_t binIndex = _hash(target) % _bins;
		typename SList<std::pair<TKey, TData>>::ConstIterator it = _data.At(binIndex).cbegin();
		while (it != _data.At(binIndex).end() && !_equality((*it).first, target))
		{
			++it;
		}
		if (it != _data.At(binIndex).end())
		{
			_data.At(binIndex).Remove(*it);
			--_size;
		}
	}

	template <typename TKey, typename TData>
	inline void HashMap<TKey, TData>::Clear()
	{
		_data.Clear();
		Allocate();
		_size = 0;

	}

	template <typename TKey, typename TData>
	inline size_t HashMap<TKey, TData>::Size() const
	{
		return _size;
	}

	template <typename TKey, typename TData>
	bool HashMap<TKey, TData>::ContainsKey(const TKey target) const
	{
		size_t binIndex = _hash(target) % _bins;
		typename SList<std::pair<TKey, TData>>::ConstIterator it = _data.At(binIndex).cbegin();
		while (it != _data.At(binIndex).end() && !_equality((*it).first, target))
		{
			++it;
		}
		return it != _data.At(binIndex).end();
	}

	template <typename TKey, typename TData>
	TData& HashMap<TKey, TData>::At(const TKey target)
	{
		Iterator it = Iterator(*this);
		size_t binIndex = _hash(target) % _bins;
		Vector<SList<std::pair<TKey, TData>>>& v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator::Iterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		while (it._listIterator != it._vecIterator->end() && !_equality((*(it._listIterator)).first, target))
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			throw std::runtime_error("At Called on Non-Existant Key");
		}
		return ((*it._listIterator).second);
	}

	template <typename TKey, typename TData>
	const TData& HashMap<TKey, TData>::At(const TKey target) const
	{
		ConstIterator it = ConstIterator(*this);
		size_t binIndex = _hash(target) % _bins;
		const Vector<SList<std::pair<TKey, TData>>>& v = _data;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::ConstIterator::ConstIterator(v, binIndex);
		it._listIterator = it._vecIterator->begin();
		while (it._listIterator != it._vecIterator->end() && !_equality((*(it._listIterator)).first, target))
		{
			++it._listIterator;
		}
		if (it._listIterator == it._vecIterator->end())
		{
			throw std::runtime_error("At Called on Non-Existant Key");
		}
		return ((*it._listIterator).second);
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::begin()
	{
		return Iterator(*this);
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::Iterator HashMap<TKey, TData>::end()
	{
		Iterator it = Iterator();
		it._container = this;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::Iterator::Iterator(_data, _data.Size());
		return it;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::begin() const
	{
		return ConstIterator(*this);
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::end() const
	{
		ConstIterator it = ConstIterator();
		it._container = this;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::ConstIterator::ConstIterator(_data, _data.Size());
		return it;
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cbegin() const
	{
		return ConstIterator(*this);
	}

	template <typename TKey, typename TData>
	typename HashMap<TKey, TData>::ConstIterator HashMap<TKey, TData>::cend() const
	{
		ConstIterator it = ConstIterator();
		it._container = this;
		it._vecIterator = Vector<SList<std::pair<TKey, TData>>>::ConstIterator::ConstIterator(_data, _data.Size());
		return it;
	}

	template <typename TKey, typename TData>
	void HashMap<TKey, TData>::Allocate()
	{
		_data.Clear();
		while (_data.Size() != _data.Capacity())
		{
			_data.PushBack(SList<std::pair<const TKey, TData>>());
		}
	}


	template <typename TKey, typename TData>
	bool HashMap<TKey,TData>::pairCompare(const std::pair<const TKey, TData>& a, const std::pair<const TKey, TData>& b)
	{
		bool eq = _equality(a.first, b.first);
		return eq;
	}
}
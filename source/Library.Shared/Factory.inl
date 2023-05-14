#pragma once
#include "Factory.h"

namespace FieaGameEngine
{
	template <typename T>
	Factory<T>* Factory<T>::Find(const std::string& name)
	{
		assert(_factories.ContainsKey(name));
		return _factories[name];
	}
	template <typename T>
	T* Factory<T>::Create(const std::string& name)
	{
		return Find(name)->CreateProduct();
	}
	template<typename T>
	void Factory<T>::Add(Factory* factory)
	{
		assert(!_factories.ContainsKey(factory->ClassName()));
		_factories.Insert(std::make_pair(factory->ClassName(), factory));
	}
	template<typename T>
	void Factory<T>::Clear()
	{
		while (_factories.Size() != 0)
		{
			auto i = _factories.begin();
			delete(i->second);
			_factories.Remove(i->first);
		}
		_factories.Clear();
	}
}
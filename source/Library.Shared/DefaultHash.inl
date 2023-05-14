#pragma once

#include <string>
#include "DefaultHash.h"

namespace FieaGameEngine
{
	inline std::size_t AutoHash(const std::byte* raw, size_t size)
	{
		const auto prime = 37;
		size_t hash = 0;
		for (std::size_t index = 0; index < size; ++index)
		{
			hash += static_cast<size_t>(raw[index]) * prime;
		}
		return hash;
	}

	inline size_t DefaultHash<int>::operator()(const int& v)
	{
		return v;
	}

	inline size_t DefaultHash<char*>::operator()(const char* v)
	{
		auto size = sizeof(char) * strlen(v);
		const std::byte* raw = reinterpret_cast<const std::byte*>(v);
		return AutoHash(raw, size);
	}

	inline size_t DefaultHash<std::string>::operator()(const std::string &v)
	{
		auto size = v.size();
		const std::byte* raw = reinterpret_cast<const std::byte*>(v.data());
		return AutoHash(raw, size);
	}

	template<typename T>
	inline size_t DefaultHash<T>::operator()(const T& v)
	{
		const std::byte* raw = reinterpret_cast<const std::byte*>(&v);
		auto size = sizeof(T);
		
		return AutoHash(raw, size);
	}
	
}
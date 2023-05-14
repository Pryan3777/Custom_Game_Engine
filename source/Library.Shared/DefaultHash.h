#pragma once

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include <string>

namespace FieaGameEngine
{
	template<class T>
	struct DefaultHash
	{
		size_t operator()(const T&);
	};

	template<>
	struct DefaultHash<int>
	{
		size_t operator()(const int&);
	};

	template<>
	struct DefaultHash<char*>
	{
		size_t operator()(const char*);
	};

	template<>
	struct DefaultHash<std::string>
	{
		size_t operator()(const std::string&);
	};


}

#include "DefaultHash.inl"
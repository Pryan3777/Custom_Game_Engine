#pragma once

#include "UserHashImplementation.h"

#include "Foo.h"
#include "DefaultHash.h"

namespace FieaGameEngine
{
	template<>
	inline size_t DefaultHash<const UnitTests::Foo>::operator()(const UnitTests::Foo & f)
	{
		const int32_t a = f.Data();
		const std::byte* raw = reinterpret_cast<const std::byte*>(&a);
		auto size = sizeof(f.Data());

		return AutoHash(raw, size);
	}
}
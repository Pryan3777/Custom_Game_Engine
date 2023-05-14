#pragma once

#include "DefaultHash.h"
#include "Foo.h"

namespace FieaGameEngine
{
	template<>
	size_t DefaultHash<const UnitTests::Foo>::operator()(const UnitTests::Foo & f);
}
#include "UserHashImplementation.inl"
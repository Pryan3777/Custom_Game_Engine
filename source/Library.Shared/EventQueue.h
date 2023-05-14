#pragma once

#include "Event.h"
#include "GameTime.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class EventQueue
	{
	public:
		static void Enqueue(std::shared_ptr<EventPublisher> e, std::chrono::duration<int, std::ratio<1, 1000>> t);
		static void Update(GameTime g);
		static void Clear();
		static bool IsEmpty();
		static size_t Size();

	private:
		static inline SList<std::shared_ptr<EventPublisher>> _events{};
	};
}

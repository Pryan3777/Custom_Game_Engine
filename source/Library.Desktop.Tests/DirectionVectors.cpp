#include "pch.h"
#include "DirectionVectors.h"
#include <cmath>


namespace FieaGameEngine
{
	std::pair<Direction, Direction> Forward(const Direction face, const Direction dir, MovementCase c)
	{
		int f = static_cast<int>(face);
		int d = static_cast<int>(dir);

		switch (c)
		{
		case MovementCase::Up:
			return std::make_pair(static_cast<Direction>(- d), static_cast<Direction>(f));
		case MovementCase::Forward:
			return std::make_pair(static_cast<Direction>(f), static_cast<Direction>(d));
		case MovementCase::Down:
			return std::make_pair(static_cast<Direction>(d), static_cast<Direction>(- f));
		}

		return std::pair<Direction, Direction>();
	}
	Direction Left(Direction face, Direction dir)
	{
		int f = static_cast<int>(face);
		int d = static_cast<int>(dir);

		return static_cast<Direction>((6 - std::abs(f) - std::abs(d)) * (((((std::abs(f) - std::abs(d)) + 3) % 3) * 2) - 3) * ((f * d) > 0 ? 1 : -1));
	}
	Direction Right(Direction face, Direction dir)
	{
		return static_cast<Direction>(- static_cast<int>(Left(face, dir)));
	}
	std::tuple<int, int, int> DirectionToVector(const Direction d)
	{
		switch (d)
		{
		case Direction::nX:
			return std::make_tuple(-1,0,0);
		case Direction::nY:
			return std::make_tuple(0, -1, 0);
		case Direction::nZ:
			return std::make_tuple(0, 0, -1);
		case Direction::X:
			return std::make_tuple(0, 0, 1);
		case Direction::Y:
			return std::make_tuple(0, 1, 0);
		case Direction::Z:
			return std::make_tuple(1, 0, 0);
		}
		return std::make_tuple(0, 0, 0);
	}
	Direction VectorToDirection(const std::tuple<int, int, int> v)
	{
		return static_cast<Direction>((std::get<0>(v) * 3) + (std::get<1>(v) * 2) + (std::get<2>(v)));
	}
}
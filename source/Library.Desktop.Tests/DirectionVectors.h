#pragma once
#include <utility>
#include <tuple>

namespace FieaGameEngine
{
	enum class MovementCase
	{
		Up,
		Forward,
		Down
	};

	enum class Direction
	{
		X = -3,
		Y,
		Z,
		Base,
		nZ,
		nY,
		nX
	};

	std::pair<Direction, Direction> Forward(const Direction face, const Direction dir, MovementCase c);
	Direction Left(const Direction face, const Direction dir);
	Direction Right(const Direction face, const Direction dir);

	std::tuple<int, int, int> DirectionToVector(const Direction d);
	Direction VectorToDirection(const std::tuple<int, int, int>);

	// TODO: Function that returns glm::vec3 from Direction, or from Tuple
}
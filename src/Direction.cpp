#include "Direction.h"
#include <iostream>
#include <stdexcept>

sf::Vector2f toVector(Direction dir)
{
	switch (dir)
	{
	case Direction::UpLeft:
		return { -1, -1 };
	case Direction::UpRight:
		return { -1, 1 };
	case Direction::Right:
		return { 0, 1 };
	case Direction::Left:
		return { 0, -1 };
	case Direction::DownRight:
		return { 1, 1 };
	case Direction::DownLeft:
		return { 1, -1 };
	case Direction::Stay:
		return { 0, 0 };
	default:
		throw std::runtime_error("Unknown direction");
	}
}

std::pair<Direction, sf::Vector2f> getDir(sf::Vector2f current, sf::Vector2f target, bool even) {
	sf::Vector2f dir;
	if (target.x - current.x > ALPHA)
		dir.x = 1;
	else if (target.x - current.x < -ALPHA)
		dir.x = -1;
	else
		dir.x = 0;
	if (target.y - current.y > ALPHA)
		dir.y = 1;
	else if (target.y - current.y < -ALPHA)
		dir.y = -1;
	else
		dir.y = 0;
	return std::pair<Direction, sf::Vector2f>(toDir(even, dir), dir);
}

Direction toDir(bool even, sf::Vector2f dir)
{
	if (dir.x == -1 && dir.y == -1 && even)
		return Direction::UpLeft;
	else if (dir.x == 1 && dir.y == -1 && even)
		return Direction::DownLeft;
	else if (dir.x == 1 && dir.y == -1 && !even)
		return Direction::UpRight;
	else if (dir.x == 1 && dir.y == 1 && !even)
		return Direction::DownRight;
	else if (dir.x == 0 && dir.y == 1)
		return Direction::Right;
	else if (dir.x == 0 && dir.y == -1)
		return Direction::Left;
	else if (dir.x == -1 && dir.y == 0)
		return (even) ? Direction::UpRight : Direction::UpLeft;
	else if (dir.x == 1 && dir.y == 0)
		return (even) ? Direction::DownRight : Direction::DownLeft;


	return Direction::Stay;
}
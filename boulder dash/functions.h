#pragma once

enum class Name { rock, wall, ground, diamond, endlvl };

enum MoveDirection { UP, DOWN, LEFT, RIGHT };

struct tilePos
{
	int x;
	int y;
};
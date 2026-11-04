#include "Entity.h"

#include <iostream>

void Entity::LoseHealth(int amount)
{
	health -= amount;

	if (health < 0)
	{
		health = 0;
	}
}

void Entity::GainHealth(int amount)
{
	health += amount;
}

void Entity::SetCoords(int newX, int newY)
{
	x = newX;
	y = newY;
}

int Entity::GetX()
{
	return x;
}

int Entity::GetY()
{
	return y;
}

void Entity::DisplayName()
{
	std::cout << name << ' ';
}

void Entity::SetName(char newName)
{
	name = newName;
}
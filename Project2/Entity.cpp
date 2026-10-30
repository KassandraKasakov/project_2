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

void Entity::Attack(Entity target)
{
	target.LoseHealth(damage);
}

void Entity::LoseOxygen(int amount)
{
	oxygen -= amount;

	if (oxygen < 0)
	{
		oxygen = 0;
		LoseHealth(1);
	}
}

void Entity::GainOxygen(int amount)
{
	oxygen += amount;
}

void Entity::SetCoords(int newX, int newY)
{
	x = newX;
	y = newY;
}

void Entity::DisplayName()
{
	std::cout << name << ' ';
}
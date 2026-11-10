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


void Entity::SetCoords(Vector2 newPos)
{
	pos = newPos;
}

void Entity::SetCoordsSlow(Vector2 newPos)
{
	int slow = rand() % 2;
	switch (slow)
	{
	case 0:
		SetCoords(newPos);
		break;
	case 1:
		break;
	}
}

Vector2 Entity::GetPos()
{
	return pos;
}


void Entity::DisplayName()
{
	std::cout << name << ' ';
}

void Entity::SetName(char newName)
{
	name = newName;
}


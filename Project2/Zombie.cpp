#include "Zombie.h"


Vector2 Zombie::GetRelativeDir(Entity* player[], Entity* ennemies[], int currentEntity)
{
	Vector2 relativeDir = { 0,0 };
	int xDiff = ennemies[currentEntity]->GetPos().x - player[0]->GetPos().x;
	int yDiff = ennemies[currentEntity]->GetPos().y - player[0]->GetPos().y;

	if (xDiff < 0)
	{
		relativeDir = { 1,0 };
	}
	else if (xDiff > 0)
	{
		relativeDir = { -1,0 };
	}
	else
	{
		if (yDiff < 0)
		{
			relativeDir = { 0,1 };
		}
		else if (yDiff > 0)
		{
			relativeDir = { 0,-1 };
		}
	}
	return relativeDir;
}

void Zombie::Move(Entity* ennemies[], int currentEntity, Map map, Entity* extraEntity[])
{
	Vector2 newDir = GetRelativeDir(extraEntity, ennemies, currentEntity);

	if (IsOtherEnemy(newDir, ennemies, currentEntity))
	{
		return;
	}

	Vector2 newPos = GetPos() + newDir;
	if (map.IsInMap(newPos))
	{
		if (map.GetTile(newPos).walkable)
		{
			if (map.GetTile(GetPos()).isSlow)
			{
				SetCoordsSlow(newPos);
			}
			else
			{
				SetCoords(newPos);
			}
		}
	}
}
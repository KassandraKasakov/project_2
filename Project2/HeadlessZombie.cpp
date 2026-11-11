#include "HeadlessZombie.h"
#include <cstdlib>

Vector2 HeadlessZombie::GetRandomDir()
{
	Vector2 randomDir = { 0,0 };
	int random = rand() % 4;

	switch (random)
	{
	case 0:
		randomDir = { 1,0 };
		break;
	case 1:
		randomDir = { -1,0 };
		break;
	case 2:
		randomDir = { 0,1 };
		break;
	case 3:
		randomDir = { 0,-1 };
		break;
	}
	return randomDir;
}

void HeadlessZombie::Move(Entity* ennemies[], int currentEntity, Map map, Entity* extraEntity[])
{
	Vector2 newDir = GetRandomDir();
	
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

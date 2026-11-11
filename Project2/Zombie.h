#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
private:
	Vector2 GetRelativeDir(Entity* player[], Entity* ennemies[], int currentEntity);
public:
	virtual void Move(Entity* ennemies[], int currentEntity, Map map, Entity* extraEntity[]) override;
};


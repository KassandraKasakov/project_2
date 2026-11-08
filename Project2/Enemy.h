#pragma once

#include "Entity.h"

class Enemy : public Entity
{
protected:
	bool IsOtherEnemy(Vector2 pos, Entity* ennemies[], int currentEnemy);
public:
	virtual void Move(Entity* ennemies[], int currentEntity, Map map) override;

	Enemy();
};


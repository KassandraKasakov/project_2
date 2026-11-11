#pragma once

#include "Enemy.h"

class HeadlessZombie : public Enemy
{
private:
	Vector2 GetRandomDir();
public:
	void Move(Entity* ennemies[], int currentEntity, Map map, Entity* extraEntity[]) override;
};


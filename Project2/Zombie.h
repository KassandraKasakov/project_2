#pragma once

#include "Enemy.h"

class Zombie : public Enemy
{
private:
public:
	virtual void Move(Entity* ennemies[], int currentEntity, Map map) override;
};


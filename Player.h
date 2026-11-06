#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
public:
	virtual void Move() override;

	Player();
};


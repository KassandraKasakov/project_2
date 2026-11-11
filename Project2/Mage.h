#pragma once

#include "Player.h"

class Mage : virtual public Player
{
public:
	Mage();

protected:
	void UseAction(Entity* players[], int currentEntity) override;
};
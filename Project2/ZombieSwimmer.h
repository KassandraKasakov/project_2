#pragma once

#include "Zombie.h"
#include "Swimmer.h"

class ZombieSwimmer : public Zombie, public Swimmer
{
private:
public:
	void Move() override;
};


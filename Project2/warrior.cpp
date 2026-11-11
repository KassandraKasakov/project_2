#include "warrior.h"

constexpr int KILL_DAMAGE = 99;
Warrior::Warrior()
{
	SetName('W');
	GainHealth(19);
}

void Warrior::OnCollision(Entity* other)
{
	other->LoseHealth(KILL_DAMAGE);
	other->SetCoords({ -10, -10 });
}
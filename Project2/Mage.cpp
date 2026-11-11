#include "Mage.h"

#include <cstdlib>

Mage::Mage()
{
	SetName('M');
}

void Mage::UseAction(Entity* players[], int currentEntity)
{
	Vector2 myPos = GetPos();
	for (int k = 0; k < NB_ENTITIES; ++k)
	{
		Vector2 pos = players[k]->GetPos();
		if (k != currentEntity
			&& std::abs(pos.x - myPos.x) <= 1
			&& std::abs(pos.y - myPos.y) <= 1)
		{
			players[k]->LoseHealth(99);
		}

	}

}
#pragma

#include "Player.h"

class Warrior : public Player
{
public:
	Warrior();
protected:
	void OnCollision(Entity* other) override;
};
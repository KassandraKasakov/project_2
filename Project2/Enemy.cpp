#include "Enemy.h"

#include <iostream>

bool Enemy::IsOtherEnemy(Vector2 pos, Entity* ennemies[], int currentEnemy)
{
    for (int k = 0; k < 5; k++) {
        if (k != currentEnemy) {
            if (ennemies[k]->GetPos() == ennemies[currentEnemy]->GetPos() + pos) {
                return true;
            }
        }
    }
    return false;
}

void Enemy::Move(Entity* ennemies[], int currentEntity, Map map)
{
    return;
}


Enemy::Enemy()
{
	SetName('X');
}

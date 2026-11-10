#pragma once

#include "Entity.h"

class Player : public Entity
{
protected:
    bool IsOtherPlayer(Vector2 pos, Entity* players[], int currentPlayer);
public:
    virtual void Move(Entity* players[], int currentEntity, Map map) override;

    Player();
};


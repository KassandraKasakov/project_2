#pragma once

#include "Entity.h"

class Player : public Entity
{
protected:
    bool IsOtherPlayer(Vector2 pos, Entity* players[], int currentPlayer);
    char ReadPlayerInputs();
    Vector2 GetDirection(char key) const;
public:
    virtual void Move(Entity* players[], int currentEntity, Map map) override;

    Player();
};


#pragma once

#include "Entity.h"

class Player : public Entity
{
protected:
    Entity* GetEntityAt(Vector2 dir, Entity* players[], int currentPlayer);
    Vector2 GetDirection(char key) const;
    static constexpr int NB_ENTITIES = 6;
    void Walk(Vector2 dir, Entity* players[], int currentEntity, Map map);
    virtual void UseAction(Entity* players[], int currentEntity);
    virtual void OnCollision(Entity* other);


public:
    virtual void Move(Entity* players[], int currentEntity, Map map, Entity* extraEntity[]) override;

    Player();
};
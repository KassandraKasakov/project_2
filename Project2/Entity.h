#pragma once

#include "Utilities.h"
#include "Map.h"

class Entity
{
private:
    int health = 1;

    Vector2 pos = Vector2{};

    char name;
public:
    void LoseHealth(int amount);
    void GainHealth(int amount);
    int GetHealth();

    virtual void Move(Entity* ennemies[], int currentEntity, Map map) = 0;

    void SetCoords(Vector2 newPos);
    // Set coords with 1 in 2 chance. Used when Entity is in Slow Tiles
    void SetCoordsSlow(Vector2 newPos);

    Vector2 GetPos();

    void DisplayName();
    void SetName(char newName);
};



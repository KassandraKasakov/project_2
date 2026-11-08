#pragma once

#include "Utilities.h"

class Entity
{
private:
    int health = 1;

    Vector2 pos = Vector2{};

    char name;
public:
    void LoseHealth(int amount);
    void GainHealth(int amount);

    virtual void Move() = 0;
    void SetCoords(Vector2 newPos);

    Vector2 GetPos();

    void DisplayName();
    void SetName(char newName);
};


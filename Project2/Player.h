#pragma once

#include "Entity.h"

class Player
{
public:
    Vector2 pos = Vector2{ -2,-2 };
    char name = 'H';
    int health;
    int damage;
};


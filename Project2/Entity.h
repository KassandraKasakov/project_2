#pragma once

class Entity
{
private:
    int health = 1;

    int damage = 1;
    int oxygen = 3;

    int x;
    int y;

    char name;
public:
    void LoseHealth(int amount);
    void GainHealth(int amount);

    void Attack(Entity target);

    void LoseOxygen(int amount);
    void GainOxygen(int amount);

    virtual void Move() = 0;
    void SetCoords(int newX, int newY);

    void DisplayName();
};


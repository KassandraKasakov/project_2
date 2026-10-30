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
    void GainHealth(int amount);

    virtual void Move() = 0;
    void SetCoords(int x, int y);

    void DisplayName();
};


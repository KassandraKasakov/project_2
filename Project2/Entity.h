#pragma once

class Entity
{
private:
    int health = 1;

    int x;
    int y;

    char name;
public:
    void LoseHealth(int amount);
    void GainHealth(int amount);

    virtual void Move() = 0;
    void SetCoords(int newX, int newY);

    void DisplayName();
};


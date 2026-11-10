#include "Player.h"

#include <iostream>

bool Player::IsOtherPlayer(Vector2 pos, Entity* players[], int currentPlayer)
{
    for (int k = 0; k < 5; k++) {
        if (k != currentPlayer) {
            if (players[k]->GetPos() == players[currentPlayer]->GetPos() + pos) {
                return true;
            }
        }
    }
    return false;
}

void Player::Move(Entity* players[], int currentEntity, Map map)
{
    char key = '\0';
    std::cin >> key;

    Vector2 dir = GetDirection(key);
    Vector2 target = GetPos() + dir;

    if (!map.IsInMap(target) || !map.GetTile(target).walkable
        || IsOtherPlayer(dir, players, currentEntity))

    {
        return;
    }
    SetPos(target);
}


Vector2 Player::GetDirection(char key) const
{
    switch (key)
    {
    case 'z':
        return { 0, -1 };
    case 's':
        return { 0, 1 };
    case 'q':
        return { -1, 0 };
    case 'd':
        return { 1, 0 };
    default:
        return { 0, 0 };
    }
}

Player::Player()
{
    SetName('H');
}

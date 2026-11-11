#include "Player.h"

#include <iostream>

Entity* Player::GetEntityAt(Vector2 dir, Entity* players[], int currentPlayer)
{
    for (int k = 0; k < 5; k++) {
        if (k != currentPlayer) {
            if (players[k]->GetPos() == players[currentPlayer]->GetPos() + dir) {
                return players[k];
            }
        }
    }
    return nullptr;
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
//L'obstacle bloque simplement le joueur.
void Player::OnCollision(Entity*)
{
}
//l'espace ne fait rien.
void Player::UseAction(Entity* [], int)
{
}

void Player::Walk(Vector2 dir, Entity* players[], int currentEntity, Map map)
{
    Vector2 target = GetPos() + dir;

    if (!map.IsInMap(target) || map.GetTile(target).walkable)
    {
        return;
    }
    Entity* other = GetEntityAt(dir, players, currentEntity);
    if (other != nullptr) {
        OnCollision(other);
        return;
    }
    SetCoords(target);
}

void Player::Move(Entity* players[], int currentEntity, Map map)
{
    char key = '\0';
    std::cin >> key;

    if (key == ' ')
    {
        UseAction(players, currentEntity);
        return;
    }
    Walk(GetDirection(key), players, currentEntity, map);
}



Player::Player()
{
    SetName('H');
}
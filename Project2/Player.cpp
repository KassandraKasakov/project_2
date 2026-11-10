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
    return;
}

Player::Player()
{
    SetName('H');
}

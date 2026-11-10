#pragma once

#include "Warrior.h"
#include "HeadlessZombie.h"
#include "Map.h"

class Game
{
public:
	Map* m_currentMap;
	bool winGame = false;

private:
	void ShowMap(Entity* player[], Entity* ennemies[]);
	void ShowStats(Entity* player[]);

	void MapReset(Entity* player[], Entity* ennemies[]);
	void EntityPlanning(int currentMap, Entity* player[], Entity* ennemies[]);

	void Init(Entity* player[], Entity* ennemies[]);
	void GameLoop(Entity* player[], Entity* ennemies[], bool victory, int currentMap);
public:
	void Run();
};



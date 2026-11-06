#pragma once
#include "Map.h"

class Game
{
public:
	Map* m_currentMap;
	bool winGame = false;

private:
	void ShowMap(Player player, Entity* ennemies[]);
	void ShowStats(Player player);

	void Init();
	void GameLoop(Player player, Entity* ennemies[], bool victory, int currentMap);
public:
	void Run();
};


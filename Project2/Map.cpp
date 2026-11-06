#include "Map.h"
#include "Player.h"

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

Map::Map(int currentMap, Player& player, Entity* ennemies[])
{

    std::string path = "maps/level_";
    path.append(std::to_string(currentMap));
    path.append(".txt");

    // Opening File
    std::ifstream level(path);


    // If error opening file
    if (!level.is_open()) {
        std::cerr << "No More Maps!";
        return;
    }

    std::string line;
    int lineMax = 0;
    int columnMax = 0;

    // Def. Map Size
    getline(level, name);

    while (std::getline(level, line)) {
        columnMax++;
        lineMax = line.size();
    }

    height = lineMax;
    width = columnMax;
    data = new int[height * width];



    // Def. Map Data
    int n = -1;
    level.clear();
    level.seekg(0);
    int currentLine = 0;
    int currentEnnemy = 0;
    getline(level, name);

    while (std::getline(level, line)) {

        for (int i = 0;i < lineMax;i++) {

            n++;

            // Detects Player
            if (line[i] == 'H') {
                data[n] = 0;
                player.x = i;
                player.y = currentLine;
            }
            // Detects Ennemy
            else if (line[i] == 'X') {
                data[n] = 0;
                ennemies[currentEnnemy]->SetCoords(i, currentLine);
                currentEnnemy++;
            }

            for (int t = 0; t < 7; t++) {
                if (line[i] == tiles[t].name) {
                    data[n] = t;
                }
            }
        }
        currentLine++;
    }

    // Closing File
    level.close();
}

Map::Tile Map::GetTile(int x, int y)
{
	int cell_pos = y * height + x;
	int cell_id = data[cell_pos];
	Tile current_tile = tiles[cell_id];
	return current_tile;
}

bool Map::IsInMap(int x, int y)
{
    if (x < 0 or x > height - 1) {
        return false;
    }
    if (y < 0 or y > width - 1) {
        return false;
    }
    return true;
}

bool Map::isDoor(int x, int y)
{
    int cell_pos = y * height + x;
    int cell_id = data[cell_pos];

    if (cell_id == Door)
    {
        return true;
    }
    return false;
}

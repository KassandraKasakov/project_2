#include "Map.h"
#include "Player.h"

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

// Parser
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
    number = currentMap;



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
                player.pos = { i,currentLine };
            }
            // Detects Ennemy
            else if (line[i] == 'X') {
                data[n] = 0;
                ennemies[currentEnnemy]->SetCoords({ i,currentLine });
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


Map::Tile Map::GetTile(Vector2 pos)
{
	int cell_pos = pos.y * height + pos.x;
	int cell_id = data[cell_pos];
	Tile current_tile = tiles[cell_id];
	return current_tile;
}

void Map::MapReset(Player& player, Entity* ennemies[])
{
    // This reset entities
    player.pos = Vector2{ -2,-2 };
    player.health = 1;

    for (int i = 0;i < 5;++i)
    {
        ennemies[i]->SetCoords(Vector2{ -10 - i,-10 - i });
    }
}

bool Map::IsInMap(Vector2 pos)
{
    if (pos.x < 0 or pos.x > height - 1) {
        return false;
    }
    if (pos.y < 0 or pos.y > width - 1) {
        return false;
    }
    return true;
}

bool Map::IsDoor(Vector2 pos)
{
    int cell_pos = pos.y * height + pos.x;
    int cell_id = data[cell_pos];

    if (cell_id == Door)
    {
        return true;
    }
    return false;
}

bool Map::IsTallGrass(Vector2 pos)
{
    int cell_pos = pos.y * height + pos.x;
    int cell_id = data[cell_pos];

    if (cell_id == Tall_Grass)
    {
        return true;
    }
    return false;
}


int Map::GetWidth()
{
    return width;
}

int Map::GetHeight()
{
    return height;
}

int* Map::GetData()
{
    return data;
}

std::string Map::GetName()
{
    return name;
}

int Map::GetNumber()
{
    return number;
}

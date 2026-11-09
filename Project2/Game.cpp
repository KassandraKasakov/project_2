#include "Game.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>
#include <fstream>


void Collision(Player& player, Entity* ennemies[]) {
    for (int i = 0; i < 5; i++) {
        if (player.pos == ennemies[i]->GetPos()) {
            player.health -= 1;
        }
    }
}


void UpdateEntities(Player& player, Entity* ennemies[], Map map, bool& victory, int currentMap) {

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    char imput = _getch();
    Vector2 dir = { 0,0 };

    int slow;



    // Player Part
    switch (imput)
    {
    case 'd':
        dir.x = 1;
        break;
    case 'q':
        dir.x = -1;
        break;
    case 'z':
        dir.y = -1;
        break;
    case 's':
        dir.y = 1;
        break;
    }
    imput = 'p';

    Vector2 newPos = player.pos + dir;

    if (map.IsInMap(newPos)) {

        Map::Tile tileType = map.GetTile(newPos);
        if (tileType.walkable)
        {
            // If the tile is slow, 1 out of 2 chance of moving
            slow = rand() % 2;
            Map::Tile currentTileType = map.GetTile(player.pos);
            if (currentTileType.isSlow) {
                switch (slow)
                {
                case 0:
                    player.pos = newPos;
                    break;
                case 1:
                    break;
                }
            }
            else {
                player.pos = newPos;
            }
        }
    }

    // Ennemies Part
    for (int i = 0;i < 5;i++)
    {
        ennemies[i]->Move(ennemies, i, map);
    }

    Collision(player, ennemies);

    if (map.IsDoor(player.pos))
    {
        victory = true;
    }

}



void StartingScreen()
{
    // Opening File
    std::ifstream start("menu/start.txt");

    std::string line;

    // Display starting screen
    while (std::getline(start, line)) {
        std::cout << line << std::endl;
    }

    // Closing File
    start.close();

    char idk;
    idk = getchar();

    system("cls");
}

void GameOver(Player player)
{
    // Ending Animation
    for (int i = 1;i < 5;i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        system("cls");

        std::string path = "menu/end";
        path.append(std::to_string(i));
        path.append(".txt");


        // Opening File
        std::ifstream ending(path);

        std::string line;
        // Display ending screen
        while (std::getline(ending, line)) {
            std::cout << line << std::endl;
        }

        // Closing File
        ending.close();
    }
}

void Victory()
{
    system("cls");

    // Opening File
    std::ifstream start("menu/vicotry.txt");

    std::string line;

    // Display starting screen
    while (std::getline(start, line)) {
        std::cout << line << std::endl;
    }

    // Closing File
    start.close();

    std::cout << "You have conquered the world!" << std::endl;
}


void Game::ShowMap(Player player, Entity* ennemies[])
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int y = 0; y < m_currentMap->GetWidth(); ++y) {
        for (int x = 0; x < m_currentMap->GetHeight(); ++x) {

            Vector2 tile = { x,y };

            Map::Tile index = m_currentMap->GetTile(tile);

            // Detects Ennemies
            bool isEnnemy = false;
            int whenEnnemy;

            for (int i = 0; i < 5; i++) {
                if (tile == ennemies[i]->GetPos()) {
                    // Display if not in tall grass
                    if (!m_currentMap->IsTallGrass(tile)) {
                        isEnnemy = true;
                        whenEnnemy = i;
                    }
                }
            }

            // Display Ennemies
            if (isEnnemy) {
                SetConsoleTextAttribute(hConsole, 4);
                ennemies[whenEnnemy]->DisplayName();
            }

            // Display Player (and if not in tall grass)
            else if (tile == player.pos) {
                if (!m_currentMap->IsTallGrass(tile)) {
                    SetConsoleTextAttribute(hConsole, 14);
                    std::cout << player.name << ' ';
                }
                else {
                    SetConsoleTextAttribute(hConsole, m_currentMap->tiles[m_currentMap->Tall_Grass].color);
                    std::cout << m_currentMap->tiles[m_currentMap->Tall_Grass].name << ' ';
                }
            }

            // Display Map
            else {
                SetConsoleTextAttribute(hConsole, index.color);
                std::cout << index.name << ' '; // La ligne ultime ?
            }
        }
        std::cout << std::endl;
    }    
}

void Game::ShowStats(Player player)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 8);
    std::cout << std::endl;
    std::cout << "Level " << m_currentMap->GetNumber() << " : " << m_currentMap->GetName() << std::endl; // Level Name
    std::cout << "Coords : " << player.pos.x << ' ' << player.pos.y << std::endl; // Player Coords
    std::cout << "Health : " << player.health << "/1" << std::endl; // Player Health
    std::cout << "Your turn";
}


void Game::MapReset(Player& player, Entity* ennemies[])
{
    // This reset entities
    player.pos = Vector2{ -2,-2 };
    player.health = 1;

    for (int i = 0;i < 5;++i)
    {
        ennemies[i]->SetCoords(Vector2{ -10 - i,-10 - i });
    }
}

void Game::EntityPlanning(int currentMap, Player& player, Entity* ennemies[])
{
    std::string path = "maps/level_";
    path.append(std::to_string(currentMap));
    path.append(".txt");

    // Opening File
    std::ifstream level(path);

    std::string line;
    int currentLine = 0;
    int currentEnnemy = 0;
    getline(level, line);

    while (std::getline(level, line))
    {
        for (int i = 0;i < m_currentMap->GetHeight();i++)
        {
            // Detects Player
            if (line[i] == 'H')
            {
                player.pos = { i,currentLine };
            }
            // Detects Ennemy
            else if (line[i] == 'X')
            {
                ennemies[currentEnnemy]->SetCoords({ i,currentLine });
                currentEnnemy++;
            }
        }
        currentLine++;
    }

    // Closing File
    level.close();
}


void Game::Init(Player player, Entity* ennemies[])
{
    srand(time(0));

    StartingScreen();

    ShowMap(player, ennemies);
    ShowStats(player);
}

void Game::GameLoop(Player player, Entity* ennemies[], bool victory, int currentMap)
{
    while (player.health != 0)
    {
        UpdateEntities(player, ennemies, *m_currentMap, victory, currentMap);

        system("cls");

        ShowMap(player, ennemies);
        ShowStats(player);

        // Victory
        if (victory)
        {
            victory = false;

            // New level
            MapReset(player, ennemies);

            currentMap++;
            Map nextMap(currentMap);
            if (nextMap.GetData() == nullptr)
            {
                winGame = true;
                return;
            }
            m_currentMap = &nextMap;
            EntityPlanning(currentMap, player, ennemies);

            system("cls");
            ShowMap(player, ennemies);
            ShowStats(player);
        }
    }
}

void Game::Run()
{
    // Variable
    bool victory = false;

    Player player = { -2, -2, 'H', 20 };
    Entity* ennemies[5];
    ennemies[0] = new HeadlessZombie();
    ennemies[1] = new HeadlessZombie();
    ennemies[2] = new HeadlessZombie();
    ennemies[3] = new HeadlessZombie();
    ennemies[4] = new HeadlessZombie();

    int currentMapNumber = 1;
    Map map(currentMapNumber);
    m_currentMap = &map;
    EntityPlanning(currentMapNumber, player, ennemies);

    // Gameplay
    Init(player, ennemies);
    GameLoop(player, ennemies, victory, currentMapNumber);
    if (winGame == true)
    {
        Victory();
        return;
    }
    GameOver(player);
}

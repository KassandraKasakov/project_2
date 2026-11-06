#include "Game.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>


void Collision(Player& player, Entity* ennemies[]) {
    for (int i = 0; i < 5; i++) {
        if (player.x == ennemies[i]->GetX() and player.y == ennemies[i]->GetY()) {
            player.health -= 1;
        }
    }
}


void UpdateEntities(Player& player, Entity* ennemies[], Map map, bool& victory, int currentMap) {

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    char imput = _getch();
    int xDir = 0;
    int yDir = 0;
    int slow;



    // Player Part
    switch (imput)
    {
    case 'd':
        xDir = 1;
        break;
    case 'q':
        xDir = -1;
        break;
    case 'z':
        yDir = -1;
        break;
    case 's':
        yDir = 1;
        break;
    }
    imput = 'p';

    int newX = player.x + xDir;
    int newY = player.y + yDir;

    if (map.IsInMap(newX, newY)) {

        Map::Tile tileType = map.GetTile(newX, newY);
        if (tileType.walkable)
        {
            // If the tile is slow, 1 out of 2 chance of moving
            slow = rand() % 2;
            Map::Tile currentTileType = map.GetTile(player.x, player.y);
            if (currentTileType.isSlow) {
                switch (slow)
                {
                case 0:
                    player.x = newX;
                    player.y = newY;
                    break;
                case 1:
                    break;
                }
            }
            else {
                player.x = newX;
                player.y = newY;
            }
        }
    }

    // Ennemies Part
    int random;
    bool isOtherEnnemy = false;

    for (int i = 0;i < 5;i++) {

        int xDir = 0;
        int yDir = 0;

        // Random direction
        random = rand() % 4;

        switch (random)
        {
        case 0:
            xDir = 1;
            break;
        case 1:
            xDir = -1;
            break;
        case 2:
            yDir = -1;
            break;
        case 3:
            yDir = 1;
            break;
        }

        // Detects if there is another ennemy
        for (int k = 0; k < 5; k++) {
            if (k != i) {
                if (ennemies[k]->GetX() == ennemies[i]->GetX() + xDir and ennemies[k]->GetY() == ennemies[i]->GetY() + yDir) {
                    isOtherEnnemy = true;
                }
            }
        }
        isOtherEnnemy = false;

        if (!isOtherEnnemy) {
            if (xDir != 0 && yDir != 0)
                std::cout << "AIIIIIIIIIIIIIIIIIIIEEEEEEEEEE" << std::endl;
            int newX = ennemies[i]->GetX() + xDir;
            int newY = ennemies[i]->GetY() + yDir;

            if (map.IsInMap(newX, newY)) {

                Map::Tile tileType = map.GetTile(newX, newY);
                if (tileType.walkable)
                {
                    // If the tile is slow, 1 out of 2 chance of moving
                    slow = rand() % 2;
                    Map::Tile currentTileType = map.GetTile(ennemies[i]->GetX(), ennemies[i]->GetY());
                    if (currentTileType.isSlow) {
                        switch (slow)
                        {
                        case 0:
                            ennemies[i]->SetCoords(newX, newY);
                            break;
                        case 1:
                            break;
                        }
                    }
                    else {
                        ennemies[i]->SetCoords(newX, newY);
                    }
                }
            }
        }
    }

    Collision(player, ennemies);

    if (map.IsDoor(player.x, player.y))
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


            Map::Tile index = m_currentMap->GetTile(x, y);

            // Detects Ennemies
            bool isEnnemy = false;
            int whenEnnemy;

            for (int i = 0; i < 5; i++) {
                if (x == ennemies[i]->GetX() and y == ennemies[i]->GetY()) {
                    // Display if not in tall grass
                    if (!m_currentMap->IsTallGrass(x, y)) {
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
            else if (x == player.x and y == player.y) {
                if (!m_currentMap->IsTallGrass(x, y)) {
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
    std::cout << "Coords : " << player.x << ' ' << player.y << std::endl; // Player Coords
    std::cout << "Health : " << player.health << "/1" << std::endl; // Player Health
    std::cout << "Your turn";
}


void Game::Init()
{
    // There will be the start of the game before the game loop
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
            m_currentMap->MapReset(player, ennemies);

            currentMap++;
            Map nextMap(currentMap, player, ennemies);
            if (nextMap.GetData() == nullptr)
            {
                winGame = true;
                return;
            }
            m_currentMap = &nextMap;
            system("cls");
            ShowMap(player, ennemies);
            ShowStats(player);
        }
    }
}

void Game::Run()
{
    bool victory = false;

    Player player = { -2, -2, 'H', 20 };

    Entity* ennemies[5];
    ennemies[0] = new Enemy();
    ennemies[1] = new Enemy();
    ennemies[2] = new Enemy();
    ennemies[3] = new Enemy();
    ennemies[4] = new Enemy();

    int currentMapNumber = 1;

    Map map(currentMapNumber, player, ennemies);
    m_currentMap = &map;

    StartingScreen();

    ShowMap(player, ennemies);
    ShowStats(player);


    GameLoop(player, ennemies, victory, currentMapNumber);
    if (winGame == true)
    {
        Victory();
        return;
    }
    GameOver(player);
}

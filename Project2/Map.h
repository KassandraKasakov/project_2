#pragma once

#include "Enemy.h"
#include "Player.h"

#include <iostream>

class Map {

public:

    //
    // Tile
    //
#pragma region Tile
    enum Tile_Type
    {
        Ground = 0,
        Water = 1,
        Mountain = 2,
        Door = 3,
        Lava = 4,
        Tall_Grass = 5,
        Quicksand = 6,
    };

    struct Tile {
        char name;
        int color;
        bool walkable = true;
        bool isSlow = false;
        bool victory = false;
    };

    const Tile ground = { '.', 2 };
    const Tile water = { '~', 3 };
    const Tile mountain = { 'A', 8, false };
    const Tile door = { 'E', 15, true, false, true };
    const Tile lava = { '=', 12 };
    const Tile tall_grass = { '#', 10 };
    const Tile quicksand = { 'O', 6, true, true };

    Tile const tiles[7] =
    { ground, water, mountain,
        door, lava, tall_grass, quicksand };

#pragma endregion
    //
    //
    //
public:
    //Map CreateMap(int currentMap, Player& player, Entity* ennemies[])
    // On peut transformer la fonction create en constructeur de la classe
    // Sauf si vous voulez charger une nouvelle carte sans détruire l'objet
    Map(int currentMap, Player& player, Entity* ennemies[]);

    // Ancien GetCell mais on renvoi directement Tile comme tiles[7] est dans la classe
    // L'utilisateur finale ne peux donc plus récupérer simplement l'index dans le tableau
    Tile GetTile(Vector2 pos); 

    void MapReset(Player& player, Entity* ennemies[]);
    bool IsInMap(Vector2 pos);

    //void OnTile(Player& player, Map map, bool& victory, int currentMap) {
    // OnTile ne faisait que check si c'était la porte
    // function plus 
    bool IsDoor(Vector2 pos);
    bool IsTallGrass(Vector2 pos);

    int GetWidth();
    int GetHeight();
    int* GetData();
    std::string GetName();
    int GetNumber();

private:
    std::string name = "null";
    int number = 0;
    int* data = nullptr;
    int width = 0;
    int height = 0;
};
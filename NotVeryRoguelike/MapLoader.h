
#pragma once

#include <vector>;

#include "Tiles.h";

namespace Game {

  struct TilePack {
    std::vector<Tile> Tiles;

    std::vector<Tile> ItemTiles;
    std::vector<Item> Items;

    std::vector<Tile> MonsterTiles;
    std::vector<Monster> Monsters;

    std::vector<Tile> NpcTiles;
    std::vector<Npc> Npcs;

    std::vector<Tile> ExitTiles;
    std::vector<Exit> Exits;
  };

  class MapLoader {
  public:
    static TilePack load(const std::string& mapName);
  };

}
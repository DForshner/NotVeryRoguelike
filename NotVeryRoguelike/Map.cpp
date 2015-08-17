/* Licensed to the Apache Software Foundation(ASF) under one
* or more contributor license agreements.See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.You may obtain a copy of the License at
*
* http ://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <cassert>
#include <random>
#include <chrono>

#include "Map.h"
#include "MapLoader.h"
#include "Console.h"
#include "Symbols.h"

namespace Game {


  void Map::load() {
    auto pack = MapLoader::load(_mapName);
    _tiles.assign(pack.Tiles.begin(), pack.Tiles.end());

    _items.assign(pack.Items.begin(), pack.Items.end());
    _itemTiles.assign(pack.ItemTiles.begin(), pack.ItemTiles.end());

    _monsters.assign(pack.Monsters.begin(), pack.Monsters.end());
    _monsterTiles.assign(pack.MonsterTiles.begin(), pack.MonsterTiles.end());

    _npcs.assign(pack.Npcs.begin(), pack.Npcs.end());
    _npcTiles.assign(pack.NpcTiles.begin(), pack.NpcTiles.end());

    _exits.assign(pack.Exits.begin(), pack.Exits.end());
    _exitTiles.assign(pack.ExitTiles.begin(), pack.ExitTiles.end());
  }

  void Map::draw() {
    std::vector<std::vector<Tile>*> foreground {
      &_itemTiles, &_monsterTiles, &_npcTiles, &_exitTiles
    };

    Console::drawTiles(_tiles, foreground, getWidth(), getHeight());
  }

  bool Map::isOccupied(const Console::Position& position) const {
    return std::any_of(_tiles.cbegin(), _tiles.cend(), 
      [&] (const auto& x) { 
        auto tilePos = x.getPosition();
        return
          tilePos.X == position.X
          && tilePos.Y == position.Y
          && x.isSolid();
      });
  }

  bool Map::isExitTile(Console::Position position) const {
    return std::any_of(_exitTiles.cbegin(), _exitTiles.cend(), 
      [&] (const auto& x) { 
        auto tilePos = x.getPosition();
        return 
          tilePos.X == position.X
          && tilePos.Y == position.Y;
      });
  }

  Exit Map::getExit(Console::Position pos) const {
    auto match = std::find_if(_exitTiles.cbegin(), _exitTiles.cend(),
      [&](const auto& cur) { 
        auto position = cur.getPosition();
        return position.X == pos.X && position.Y == pos.Y;
      });
    assert(match != _exitTiles.cend()); // Expected to find tile
    auto index = std::distance(_exitTiles.cbegin(), match);
    return _exits[index];
  }

  void Map::insert(Tile tile, Console::Position pos) {

    auto match = std::find_if(_tiles.begin(), _tiles.end(),
      [&](const auto& cur) { 
        auto position = cur.getPosition();
        return position.X == pos.X && position.Y == pos.Y;
      });

    if (match != _tiles.end()) {
      *match = tile;
    } else {
      // Tile does not exit
    }
  }

  void Map::insert(Item item, Tile tile, int x, int y) {
    _items.emplace_back(item);
    _itemTiles.emplace_back(tile);
  }

  void Map::insert(Monster monster, Tile tile, int x, int y) {
    _monsters.emplace_back(monster);
    _monsterTiles.emplace_back(tile);
  }

  void Map::insert(Npc npc, Tile tile, int x, int y) {
    _npcs.emplace_back(npc);
    _npcTiles.emplace_back(tile);
  }

  void Map::insert(Exit exit, Tile tile, int x, int y) {
    _exits.emplace_back(exit);
    _exitTiles.emplace_back(tile);
  }

  void Map::save() {

  }

  void Map::updateNPCs() {
    // TODO: Make more fancy
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed1);
    std::uniform_int_distribution<int> distribution(0, 5000);

    for (auto i = 0; i < _npcs.size(); ++i) {
      auto r = distribution(generator);

      if (r % 500 != 0) { continue; }
        
      Console::Position newPos{ _npcTiles[i].getPosition() };
      switch (r % 4) {
        case 0: newPos.X++; break;
        case 1: newPos.X--; break;
        case 2: newPos.Y++; break;
        case 3: newPos.Y--; break;
      }

      if (!isOccupied(newPos)) {
        // TODO: Trigger needs redraw
        Tile oldTile = _npcTiles[i];
        Tile newTile(newPos, oldTile.getSymbol(), oldTile.isSolid());
        _npcTiles[i] = newTile;
      }

    }
  }

  bool Map::isOccupiedByNPC(const Console::Position& pos) const {
    return std::any_of(_npcTiles.cbegin(), _npcTiles.cend(),
      [&](const auto& npc) { return npc.getPosition().X == pos.X && npc.getPosition().Y == pos.Y; });
  }

  const Npc* Map::getNpc(const Console::Position& pos) const {
    auto tile = std::find_if(_npcTiles.cbegin(), _npcTiles.cend(),
      [&](const auto& npc) { return npc.getPosition().X == pos.X && npc.getPosition().Y == pos.Y; });
    auto idx = std::distance(_npcTiles.cbegin(), tile);
    return &_npcs[idx];
  }
}

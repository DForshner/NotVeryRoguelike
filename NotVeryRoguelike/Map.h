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

#pragma once

#include <string>
#include <vector>
#include <stdio.h>

#include "Console.h"
#include "Tiles.h"

namespace Game {

  class Map {

  public:
    Map(std::string mapName) :
      _mapName(mapName),
      _hasUnsavedChanges(false)
    {}

    void load();

    void draw();

    int getWidth() const { return 80; }
    int getHeight() const { return 45; }

    bool isOccupied(const Console::Position& position) const;

    bool isExitTile(Console::Position position) const;
    Exit getExit(Console::Position position) const;

    bool isOccupiedByNPC(const Console::Position& position) const;
    const Npc* getNpc(const Console::Position& position) const;

    void insert(Tile tile, Console::Position pos);
    void insert(Item item, Tile tile, int x, int y);
    void insert(Monster monster, Tile tile, int x, int y);
    void insert(Npc npc, Tile tile, int x, int y);
    void insert(Exit exit, Tile tile, int x, int y);

    bool hasUnsavedChanges() const { return _hasUnsavedChanges; }
    void save();

    void updateNPCs();

  private:
    std::string _name;
    std::vector<Tile> _tiles;

    std::vector<Tile> _itemTiles;
    std::vector<Item> _items;

    std::vector<Tile> _monsterTiles;
    std::vector<Monster> _monsters;

    std::vector<Tile> _npcTiles;
    std::vector<Npc> _npcs;

    std::vector<Tile> _exitTiles;
    std::vector<Exit> _exits;

    std::string _mapName;
    bool _hasUnsavedChanges;
  };

}
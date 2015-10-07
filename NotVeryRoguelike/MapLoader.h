/* Licensed to the Apache Software Foundation(ASF) under one
* or more contributor license agreements.See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#pragma once

#include <vector>;

#include "Tiles.h";
#include "EntityManager.h"

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
    static TilePack load(const std::string& mapName, EntityManager& entities);

  };

}
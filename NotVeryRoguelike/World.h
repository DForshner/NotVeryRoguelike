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

#include <random>

#include "Player.h"
#include "Symbols.h"
#include "Events.h"
#include "Map.h"
#include "Console.h"
#include "Music.h"
#include "Menu.h"
#include "EntityManager.h"
#include "MapLoader.h"

const int WIDTH{ 80 };
const int HEIGHT{ 45 };
using FrameTime = float;

namespace Game {

  constexpr int PLAYER_START_X = 25;
  constexpr int PLAYER_START_Y = 25;
  constexpr auto DEFAULT_MAP = "Default";
  constexpr auto DEFAULT_SONG = "Default";

  class World {

  public:
    World() :
      _player(Console::PLAYER, { PLAYER_START_X, PLAYER_START_Y }),
      _map(std::string{ DEFAULT_MAP }, _entities),
      _needsRedraw(true), // Initial map draw
      _playerPaused(false)
    {
      _map.load();
    }

    bool isPlayerAlive() const { return _player.isAlive(); }

    std::vector<Event> handleEvents(std::vector<Event>& events);

    void update();

  private:
    Player _player;
    Map _map;
    EntityManager _entities;

    bool _needsRedraw;
    bool _playerPaused;
    int _selectedTile = 1;

    void handlePlayerMove(Console::Position newPosition);
    void handleInsert(Console::Position position);

    void interactWithNPC(const Console::Position& pos);
    void handleEvent(Event e, std::vector<Event>& toSchedule);
    void draw();
  };

}
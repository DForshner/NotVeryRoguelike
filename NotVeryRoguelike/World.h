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

#include <random>

#include "Player.h"
#include "Symbols.h"
#include "Events.h"
#include "Map.h"
#include "Console.h"
#include "Music.h"
#include "Menu.h"

namespace Game {

  constexpr int PLAYER_START_X = 25;
  constexpr int PLAYER_START_Y = 25;
  constexpr auto DEFAULT_MAP = "Default";
  constexpr auto DEFAULT_SONG = "Default";

  class World {

  public:
    World() :
      _player(Console::PLAYER, { PLAYER_START_X, PLAYER_START_Y }),
      _map(std::string{ DEFAULT_MAP }),
      _needsRedraw(true), // Initial map draw
      _drawMenu(false),
      _distribution(0, 3)
    {
      _map.load();
      _music.play(DEFAULT_SONG);

      //std::default_random_engine generator();
      //std::uniform_real_distribution<int> distribution(0, 11);
      //auto r = distribution(generator);
    }

    bool isPlayerAlive() const { return _player.isAlive(); }

    void draw();

    void handleInput(Event event);

    void updateNPCs();

  private:
    Player _player;
    Map _map;
    Music _music;
    Menu _menu;
    std::default_random_engine _generator;
    std::uniform_int_distribution<int> _distribution;

    bool _needsRedraw;
    bool _drawMenu;

    void handlePlayerMove(Console::Position newPosition);
    void handleInsert(Console::Position position);
    int genRandZeroToThree() { return _distribution(_generator); }

    void interactWithNPC(const Console::Position& pos);
  };

}
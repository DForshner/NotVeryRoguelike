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

#include <algorithm>>

#include "World.h"

namespace Game {

  void World::draw() {

    if (_needsRedraw) {
      _map.draw();
      _needsRedraw = false;
    }

    Console::draw(Console::PLAYER, _player.getPosition());

    if (_drawMenu) {
      // Draw menu
    }
  }

  void World::handleInput(Event event) {
    switch (event.Type) {
      case EventTypes::UP:
        handlePlayerMove(_player.getPosition(Directions::UP));
        break;
      case EventTypes::DOWN:
        handlePlayerMove(_player.getPosition(Directions::DOWN));
        break;
      case EventTypes::LEFT:
        handlePlayerMove(_player.getPosition(Directions::LEFT));
        break;
      case EventTypes::RIGHT:
        handlePlayerMove(_player.getPosition(Directions::RIGHT));
        break;
      case EventTypes::SPACE:
        handleInsert(_player.getPosition());
        break;
      case EventTypes::ESCAPE:
        _menu.launchMenu();
        break;
    }
  }
    
  void World::handlePlayerMove(Console::Position newPosition) {
    if (!_map.isOccupied(newPosition)) {
      _player.move(newPosition);
      _needsRedraw = true;
    }

    if (_map.isOccupiedByNPC(newPosition)) {
      _player.undoMove();
    }

    if (_map.isExitTile(newPosition)) {

      if (_map.hasUnsavedChanges()) {
        // TODO: Ask player
        _map.save();
      }

      auto exit = _map.getExit(newPosition);
      _player.move(exit.getDestination());
      auto mapName = exit.getMapName();
      _map = Map{ mapName };
      _map.load();

      _needsRedraw = true;
    }
  }

  void World::handleInsert(Console::Position position) {
    Tile tree{ position, Console::TREE, false };
    _map.insert(tree, position);
  }

  void World::updateNPCs() {
    _map.updateNPCs();
  }

  void World::interactWithNPC(const Console::Position& pos) {
    auto npc = _map.getNpc(pos);

    //Console::displayDialog(npc.getName(), npc.getMessage());
  }

}
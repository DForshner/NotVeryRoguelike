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

#include <Windows.h>
#include <memory>
#include <string>

#include "Tiles.h"
#include "Symbols.h" 

namespace Console {

  void init();

  void draw(const Symbol& symbol, const Position& position);

  void drawTiles(
    const std::vector<Game::Tile>& tiles, 
    const std::vector<std::vector<Game::Tile>*>& foreground,
    int width, int height);

  void displayDialog(std::string name, std::string msg);

  void drawBox(int width, int height, int x, int y);

  void drawString(int x, int y, const std::string& s, const Color& color);
}
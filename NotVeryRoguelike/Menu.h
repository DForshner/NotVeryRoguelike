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

#include "Events.h"
#include <string>
#include <vector>
#include <memory>

namespace Game {

  enum class MenuTypes {
    NONE,
    MAIN,
    INVENTORY,
    EDITOR,
    EDITOR_TILE
  };

  struct MenuItem {
    std::string Name;
    Event Trigger;
  };

  class Menu {

  public:
    Menu(int width, int height) : 
      _width(width), 
      _height(height),
      _current(MenuTypes::NONE)
    {}

    // Draw a message box in the center of the screen
    void drawMessageBox(std::string msg);

    std::vector<Event> handleEvents(std::vector<Event>& events);

  private:
    int _width{ 0 };
    int _height{ 0 };

    MenuTypes _current;
    std::vector<MenuItem> _currentItems;

    int _menuIdx{ 0 };
    bool _needsRedraw{ true };

    void handleEvent(Event e, std::vector<Event>& toSchedule);

    void drawMainMenu();
    void drawInventoryMenu();
    void drawEditorMenu();
    void drawEditorTileMenu();

    void handleMenuShowHide(Event event);
    void draw();
    void drawMenu(const std::vector<MenuItem>& items);
  };

}
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

#include "Menu.h"
#include "Console.h"
#include "Symbols.h"
#include <assert.h>
#include <vector>
#include <algorithm>

namespace Game {

  constexpr int MENU_WIDTH{ 3 };
  constexpr int MENU_HEIGHT{ 3 };
  constexpr int MENU_START_X{ 3 };
  constexpr int MENU_START_Y{ 3 };
  constexpr int MARGIN_EDGE_TO_BOX{ 3 };
  constexpr int MARGIN_BOX_TO_TEXT{ 2 };
  constexpr char* CURSOR{ " > " };
  constexpr int CURSOR_MARGIN{ 3 };

  void Menu::draw() {
    switch (_current) {
      case MenuTypes::NONE:
        break;
      case MenuTypes::MAIN:
        drawMainMenu();
        break;
      case MenuTypes::INVENTORY:
        drawInventoryMenu();
        break;
      case MenuTypes::EDITOR:
        drawEditorMenu();
        break;
    }
  }

  void Menu::drawMainMenu() {
    std::vector<MenuItem> items { 
      { "Inventory", { EventTypes::MENU_INVENTORY_SELECTED } },
      { "Editor", { EventTypes::MENU_EDITOR_SELECTED } },
      { "Load", { EventTypes::MENU_LOAD_SELECTED } },
      { "Save", { EventTypes::MENU_SAVE_SELECTED } },
      { "Quit", { EventTypes::MENU_EXIT_SELECTED } }
    };
    _currentItems = std::move(items);
    drawMenu(_currentItems);
  }

  void Menu::drawInventoryMenu() {
    std::vector<MenuItem> items { 
      { "Use", { EventTypes::NOOP} },
      { "Equip", { EventTypes::NOOP} },
      { "Unequip", { EventTypes::NOOP} },
      { "Drop", { EventTypes::NOOP} }
    };
    _currentItems = std::move(items);
    drawMenu(_currentItems);
  }

  void Menu::drawEditorMenu() {
    std::vector<MenuItem> items { 
      { "Tile", { EventTypes::NOOP} },
      { "Monster", { EventTypes::NOOP} },
      { "NPC", { EventTypes::NOOP} },
      { "Item", { EventTypes::NOOP} },
      { "Exit", { EventTypes::NOOP} }
    };
    _currentItems = std::move(items);
    drawMenu(_currentItems);
  }

  void Menu::drawMenu(const std::vector<MenuItem>& items) {

    auto maxTextWidthElement = std::max_element(items.cbegin(), items.cend(),
      [](MenuItem a, MenuItem b) { return a.Name.length() < b.Name.length(); });
    auto maxTextWidth = (maxTextWidthElement != items.cend()) ? maxTextWidthElement->Name.length() : 0;

    auto boxWidth = maxTextWidth + (2 * MARGIN_BOX_TO_TEXT) + CURSOR_MARGIN;
    auto boxStartX = (_width / 2) - (boxWidth / 2);

    auto numLines = items.size();
    auto boxHeight = numLines + 2;
    auto boxStartY = (_height / 2) - (boxHeight/ 2);
    Console::drawBox(boxWidth, boxHeight, boxStartX, boxStartY);

    auto textStartX = boxStartX + 1;
    auto textStartY = boxStartY + 1;
    for (auto i = 0; i < items.size(); ++i) {
      Console::drawString(textStartX + CURSOR_MARGIN, (textStartY + i), items[i].Name, Console::MENU_COLOR);
    }
      
    Console::drawString(textStartX, (textStartY + _menuIdx), { CURSOR }, Console::MENU_COLOR);

    _needsRedraw = false;
  }

  void Menu::drawMessageBox(std::string msg) {
    auto maxTextWidth = (_width - (2 * MARGIN_EDGE_TO_BOX) - (2 * MARGIN_BOX_TO_TEXT));

    auto numLines = (msg.length() / maxTextWidth) + 1;

    // M1<---maxBoxWidth--->M1   (M1 = Margin from box to screen edge)
    // M1|M2<---TEXT---->M1|M1   (M2 = Margin from text to box edge)
    auto textWidth = (numLines > 1) ? maxTextWidth : static_cast<int>(msg.length());
    auto boxWidth = textWidth + (2 * MARGIN_BOX_TO_TEXT);
    auto boxHeight = numLines + 2; // Top + Body (Lines) + Bottom

    auto startX = (_width / 2) - (boxWidth / 2);
    auto startY = (_height / 2) - (boxHeight / 2);

    // #------#
    // |      |
    // #------#
    Console::drawBox(boxWidth, boxHeight, startX, startY);

    // #------#
    // | TEXT |
    // #------#
    for (auto i = 0; i < boxHeight - 2; ++i) {
      auto lineStart = i * textWidth;
      auto fullLineEnd = lineStart + textWidth;
      auto lineEnd = min(fullLineEnd, msg.length());
      auto line = msg.substr(lineStart, lineEnd - lineStart);

      auto test = line.length();

      Console::drawString(startX + MARGIN_BOX_TO_TEXT, startY + 1 + i, line, Console::MENU_COLOR);
    }
  }

  void Menu::handleMenuShowHide(Event event) {
    switch (_current) {
      case MenuTypes::NONE:
        _current = MenuTypes::MAIN;
        _menuIdx = 0;
        _needsRedraw = true;
        break;
      case MenuTypes::MAIN:
        _current = MenuTypes::NONE;
        break;
      case MenuTypes::INVENTORY:
        _current = MenuTypes::MAIN;
        _menuIdx = 0;
        _needsRedraw = true;
        break;
    }
  }

  void Menu::handleEvent(Event e, std::vector<Event>& toSchedule) {
    if (e.Type == EventTypes::ESCAPE) {
      handleMenuShowHide(e);

      if (_current != MenuTypes::NONE) {
        toSchedule.emplace_back(Event{ EventTypes::PLAYER_PAUSE_INPUT });
        _needsRedraw = true;
      } else {
        toSchedule.emplace_back(Event{ EventTypes::PLAYER_RESUME_INPUT });
        toSchedule.emplace_back(Event{ EventTypes::REQUEST_MAP_REDRAW });
      }
    }

    if (_current == MenuTypes::NONE) {
      return;
    }

    switch (e.Type) {
      case EventTypes::UP:
        _menuIdx -= 1;
        _needsRedraw = true;
        break;
      case EventTypes::DOWN:
        _menuIdx += 1;
        _needsRedraw = true;
        break;
      case EventTypes::SPACE: {
        auto selected = _currentItems[_menuIdx];
        toSchedule.emplace_back(selected.Trigger);
        break;
      }
      case EventTypes::MENU_INVENTORY_SELECTED:
        _current = MenuTypes::INVENTORY;
        draw();
        break;
      case EventTypes::MENU_EDITOR_SELECTED:
        _current = MenuTypes::EDITOR;
        draw();
        break;
      case EventTypes::REQUEST_MENU_REDRAW:
        draw();
        break;
    }
  }

  std::vector<Event> Menu::handleEvents(std::vector<Event>& events) {
    std::vector<Event> toSchedule;

    for (auto i = 0; i < events.size(); ++i) {
      handleEvent(events[i], toSchedule);
    }

    if (_needsRedraw) {
      toSchedule.emplace_back(Event{ EventTypes::REQUEST_MENU_REDRAW });
      _needsRedraw = false;
    }

    return std::move(toSchedule);
  }

}
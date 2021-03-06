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

#include <string>
#include <memory>

enum class EventTypes {
  NOOP,

  UP,
  DOWN,
  LEFT,
  RIGHT,
  ESCAPE,
  SPACE,

  MOUSE_LEFT,
  MOUSE_RIGHT,
  MOUSE_MOVE,

  MENU_INVENTORY_SELECTED,
  MENU_INVENTORY_USE_SELECTED,

  MENU_EDITOR_SELECTED,
  MENU_EDITOR_TILE_SELECTED,
  MENU_EDITOR_MONSTER_SELECTED,

  EDITOR_TILE_SELECTED,

  MENU_LOAD_SELECTED,
  MENU_SAVE_SELECTED,
  MENU_EXIT_SELECTED,

  PLAYER_PAUSE_INPUT,
  PLAYER_RESUME_INPUT,

  REQUEST_MAP_REDRAW,
  REQUEST_MENU_REDRAW 
};

enum ValueType {
  NONE,
  INT_TYPE,
  STRING_TYPE
};

struct Value {
  ValueType type;
  union {
    int intValue;
    //std::unique_ptr<std::string> stringValue;
  };
};

struct Event {
  EventTypes type;
  Value value;
  
  Event(EventTypes type) : type(type), value{ ValueType::NONE } {}
  Event(EventTypes type, Value value) : type(type), value(value) {}
};
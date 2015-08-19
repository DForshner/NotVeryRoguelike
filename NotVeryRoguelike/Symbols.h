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

#include <Windows.h>

namespace Console {

  struct Position {
    int X{ 0 };
    int Y{ 0 };

    Position(const Position& other) : X(other.X), Y(other.Y) {}
    Position(int x, int y) : X(x), Y(y) {}
    Position(const COORD& other): X(other.X), Y(other.Y) {}

    COORD getCoord() const {
      return COORD{ (short)X, (short)Y };
    }
  };

  struct Color {
    WORD Attribute;

    Color(WORD attribute) : Attribute(attribute) {}
  };

  struct Symbol {
    CHAR_INFO Char;
    Symbol(CHAR_INFO c) : Char(c) {}
  };

  const Symbol PLAYER{ CHAR_INFO{ 0x40, FOREGROUND_RED | FOREGROUND_GREEN } };

  const Symbol TREE{ CHAR_INFO{ 0x23, FOREGROUND_GREEN } };

  const Symbol WALL_V{ CHAR_INFO{ 0xBA } };

  const Symbol WALL_H{ CHAR_INFO{ 0xCD } };

  const Color TEXT_COLOR { 
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
    FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_INTENSITY 
  };
}
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

#include "Console.h"

namespace Game {

  enum class Directions {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
  };

  class Player {
  public:
    Player(Console::Symbol image, Console::Position position);

    Console::Position getPosition() const noexcept;
    Console::Position getPosition(const Directions& direction) const noexcept;

    void move(Console::Position position);

    void undoMove() { _position = _lastPosition; }

    bool isAlive() const noexcept { return _health > 0; }

  private:
    Console::Position _position;
    Console::Position _lastPosition;
    Console::Symbol _image;

    int _health = 0;
    int _healthMax = 0;
    int _strength = 0;
    int _protection = 0;
    int _experience = 0;
    int _level = 0;
    int _gold = 0;
  };

}
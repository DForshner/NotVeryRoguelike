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

#include "Player.h"

namespace Game {

  Player::Player(Console::Symbol image, Console::Position position) :
    _image(image),
    _position(position), _lastPosition(position),
    _health(50), _healthMax(50), _strength(3), _protection(3), _experience(0), _level(1), _gold(25) 
  {}

  Console::Position Player::getPosition() const {
    return { _position.X, _position.Y };
  }

  Console::Position Player::getPosition(const Directions& direction) const {
    switch (direction) {
      case Directions::UP:
        return { _position.X, _position.Y - 1 };
      case Directions::DOWN:
        return { _position.X, _position.Y + 1 };
      case Directions::LEFT:
        return { _position.X - 1, _position.Y };
      case Directions::RIGHT:
        return { _position.X + 1, _position.Y };
    }

    return { _position.X, _position.Y };
  }

  void Player::move(Console::Position position) {
    _lastPosition = _position;
    _position = position;
  }

}
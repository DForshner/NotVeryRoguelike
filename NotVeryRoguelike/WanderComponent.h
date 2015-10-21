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

#include <functional>
#include <algorithm> 
#include <random>
#include <chrono>

#include "PositionComponent.h"
#include "NullComponent.h"
#include "Entity.h"
#include "Console.h"
#include "Map.h"

namespace Game {

  struct WanderComponent : Component {
    PositionComponent* _position;
    Map& _map;

    WanderComponent(Map& map) : _map(map) {}

    void init() override {
      _position = &_entity->getComponent<PositionComponent>();
    }

    void update(float mFT) override {

      // TODO: Make more fancy :-)
      unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
      std::default_random_engine generator(seed1);
      std::uniform_int_distribution<int> distribution(0, 5000);

      auto r = distribution(generator);

      if (r % 500 != 0) { return ; } // Do nothing

      int x = _position->x;
      int y = _position->y;

      switch (r % 4) {
        case 0: x++; break;
        case 1: x--; break;
        case 2: y++; break;
        case 3: y--; break;
      }

      // Check if destination tile is solid 

      // Check if destination tile is occupied
    }

  };

}

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

#include "Constants.h"
#include "Entity.h"

#include <vector>
#include <memory>
#include <array>

namespace Game {

  // An aggregate of entities.  Handles entity retrieval, addition, and removal
  // from game world.
  struct EntityManager {
  public:
    EntityManager() {}

    void update(float mFT);
    void draw();
    void refresh();

    Entity& addEntity();

    void addToGroup(Entity* entity, GroupId groupId);
    std::vector<Entity*>& getEntitiesByGroup(GroupId groupId);

  private:
    std::vector<std::unique_ptr<Entity>> _entities;

    // Array indexed by group id.  Each array bucket contains a vector of
    // entities that are currently in that group.
    std::array<std::vector<Entity*>, MAX_GROUPS> _groupedEntities;
  };

}
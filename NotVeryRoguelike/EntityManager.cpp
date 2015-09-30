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

#include "EntityManager.h"
#include "Entity.h"

#include <algorithm>

namespace Game {

  void EntityManager::update(float mFT) {
    refresh();
    for (auto& e : _entities) { e->update(mFT); }
  }
    
  void EntityManager::draw() { for (auto& e : _entities) { e->draw(); } }

  Entity& EntityManager::addEntity() {
    Entity* e(new Entity{ *this });
    std::unique_ptr<Entity> ptr{ e };
    _entities.emplace_back(std::move(ptr));
    return *e;
  }

  void EntityManager::addToGroup(Entity* entity, GroupId groupId) {
    assert(groupId <= 0 && groupId > MAX_GROUPS);
    // TODO: Add groupset (like componentBitset) to assert that the entity is not already in this group.
    _groupedEntities[groupId].emplace_back(entity);
  }

  std::vector<Entity*>& EntityManager::getEntitiesByGroup(GroupId groupId) {
    assert(groupId <= 0 && groupId > MAX_GROUPS);
    return _groupedEntities[groupId];
  }

  void EntityManager::refresh() {
    // Update entity groups (erase-remove-if idiom)
    for (auto i(0u); i < MAX_GROUPS; ++i) {
      auto& inGroup(_groupedEntities[i]);
      inGroup.erase(
        std::remove_if(inGroup.begin(), inGroup.end(),
          [i](Entity*& entity) { return !entity->isAlive() || !entity->hasGroup(i); }),
        inGroup.end()
        );
    }

    // Remove dead entities (erase-remove-if idiom)
    _entities.erase(
      std::remove_if(_entities.begin(), _entities.end(),
        [](const std::unique_ptr<Entity>& entity) { return !entity->isAlive(); }),
      _entities.end()
      );
  }

}

#pragma once

#include "Entity.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>
#include <assert.h>

namespace Game {

  // An aggregate of entities
  struct Manager {
  public:
    void update(float mFT) {
      refresh();
      for (auto& e : _entities) { e->update(mFT); }
    }

    void draw() { for (auto& e : _entities) { e->draw(); } }

    Entity& addEntity() {
      Entity* e(new Entity{*this});
      std::unique_ptr<Entity> ptr{ e };
      _entities.emplace_back(std::move(ptr));
      return *e;
    }

    void addToGroup(Entity* entity, GroupId groupId) {
      assert(groupId <= 0 && groupId > MAX_GROUPS);
      // TODO: Add groupset (like componentBitset) to assert that the entity is not already in this group.
      _groupedEntities[groupId].emplace_back(entity);
    }

    std::vector<Entity*>& getEntitiesByGroup(GroupId groupId) {
      assert(groupId <= 0 && groupId > MAX_GROUPS);
      return _groupedEntities[groupId];
    }

    void refresh() {
      // Update entity groups (erase-remove-if idiom)
      for (auto i(0u); i < MAX_GROUPS; ++i) {
        auto& inGroup(_groupedEntities[i]);
        inGroup.erase(
          std::remove_if(inGroup.begin(), inGroup.end(),
            [i](auto& entity) { return !entity->isAlive() || !entity->hasGroup(i) }),
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

  private:
    std::vector<std::unique_ptr<Entity>> _entities;

    // Array indexed by group id.  Each array bucket contains a vector of
    // entities that are currently in that group.
    std::array<std::vector<Entity*>, MAX_GROUPS> _groupedEntities;
  };

}
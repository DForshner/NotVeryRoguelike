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

#include "Component.h"
#include "Constants.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>
#include <assert.h>

namespace Game {

  namespace Internal {
    // Returns a globally unique id each call (0, 1, etc...)
    inline ComponentId getUniqueComponentId() noexcept {
      static ComponentId lastId{ 0u }; // Only init once ever 
      return lastId++;
    }
  }

  // Returns a unique id for each component type T
  template<typename T> inline ComponentId getComponentId() noexcept {
    // Check function is only called from type that inherit from component
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    static ComponentId typeId{ Internal::getUniqueComponentId() }; // Init once per type T
    return typeId;
  }

  using ComponentArray = std::array<Component*, MAX_COMPONENTS>; // Typedef

  class EntityManager; // forward declaration

  // An aggregate of components
  class Entity {
  public:
    Entity(EntityManager& manager) : _manager(manager) {}

    void init();
    void update(float mFT);
    void draw();
    void cleanup();

    bool isAlive() const { return _isAlive; }
    void destroy() { _isAlive = false; }

    template <typename T>
    T& getComponent() const {
      assert(hasComponent<T>());
      auto ptr(_componentArray[getComponentId<T>()]);
      return *reinterpret_cast<T*>(ptr); // cast to derived component type
    }

    template<typename T> 
    bool hasComponent() const noexcept {
      return _componentBitset[getComponentId<T>()];
    }

    template<typename T>
    void addComponent(std::unique_ptr<T> c) {}

    bool hasGroup(GroupId id) const noexcept {
      return _groupBitset[id];
    }

    void addGroup(GroupId id) noexcept {};

    void deleteGroup(GroupId groupId) noexcept {
      _groupBitset[groupId] = false;
    }

  private:
    EntityManager& _manager;

    bool _isAlive{ true };
    bool _isInitialized{ false };
    std::vector<std::unique_ptr<Component>> _components;

    // Component bitset (check if component has entity with simple bitwise AND):
    // [ 0 0 0 0 0 1 0 0 1 ]
    //             |     |
    //             |     \_ Entity has component type #0 
    //             \_______ Entity has component type #3
    ComponentBitset _componentBitset;

    // Component array (find components in constant time)
    // [0] = Component type #0
    // [1] = nullptr
    // [2] = nullptr
    // [3] = Component type #3
    ComponentArray _componentArray;

    GroupBitset _groupBitset;
  };

}
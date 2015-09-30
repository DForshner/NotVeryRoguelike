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

#include "Entity.h" 
#include "EntityManager.h"

namespace Game {

  void Entity::init() {
    _isInitialized = true;
  }
    
  void Entity::update(float mFT) { 
    for (auto& c : _components) c->update(mFT); 
    // while (!_componentsToRemove.empty()) remove(_partsToRemove.remove(0));
    // while (!_componentsToAdd.empty()) remove(_partsToAdd.remove(0));
  }

  void Entity::draw() { for (auto& c : _components) c->draw(); }

  void Entity::cleanup() {
    for (auto& c : _components) { c->cleanup(); }
    _isAlive = false;
  }

  //template<typename T>
  //void Entity::addComponent() {}

  // T is type of derived component to add 
  // TArgs is a parameter pack to pass to component T's constructor 
  //T& Entity::addComponent(TArgs&&... mArgs) {

  //template<typename T>
  //void addComponent(std::unique_ptr<T> c) {

    //c->entity = this; // Set component's parent entity
    //_components.emplace_back(std::move(ptr)); // move because unique cannot be copied

    //_componentArray[getComponentId<T>()] = c;
    //_componentBitset[getComponentId<T>()] = true;

    //c->init();

    //return *c; // return reference to the newly created component
  //}

  //template<typename T, typename... TArgs>
  //void Entity::addComponent(TArgs&&... mArgs) {
    //assert(!hasComponent<T>());

    //T* c;

    // Allocate component of type T perfectly forwarding passed args to its constructor.
    //T* c(new T(std::forward<TArgs>(mArgs)...));

    //c->entity = this; // Set component's parent entity
    //auto ptr = std::make_unique(c);
    //_components.emplace_back(std::move(ptr)); // move because unique cannot be copied

    //_componentArray[getComponentId<T>()] = c;
    //_componentBitset[getComponentId<T>()] = true;

    //c->init();

    //return *c; // return reference to the newly created component
  //}

  template<typename T> 
  T& Entity::getComponent() const {
    assert(hasComponent<T>());
    auto ptr(componentArray[getComponentId<T>()]);
    return *static_cast<T*>(ptr); // cast to derived component type
  }

  //void Entity::addGroup(GroupId id) noexcept {
    //_groupBitset[id] = true;
    //_manager.addToGroup(this, id);
  //}

}

//
//#include <vector>
//#include <memory>
//#include <algorithm>
//#include <iostream>
//#include <bitset>
//#include <array>
//#include <assert.h>
//
//namespace Game {
//
//  using ComponentId = std::size_t; // Typedef
//
//  namespace Internal {
//    // Returns a globally unique id each call (0, 1, etc...)
//    inline ComponentId getUniqueComponentId() noexcept {
//      static ComponentId lastId{ 0 }; // Only init once ever 
//      return lastId++;
//    }
//  }
//
//  class Component;
//
//  // Returns a unique id for each component type T
//  template<typename T> inline ComponentId getComponentId() noexcept {
//    // Check function is only called from type that inherit from component
//    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
//
//    static ComponentId typeId{ getUniqueComponentId() }; // Init once per type T
//    return typeId;
//  }
//
//  constexpr std::size_t MAX_COMPONENTS{ 32 };
//  using ComponentBitset = std::bitset<MAX_COMPONENTS>; // Typedef
//  using ComponentArray = std::array<Component*, MAX_COMPONENTS>; // Typedef
//
//  class Entity; // Forward declaration
//
//  struct Component {
//    Entity* entity{ nullptr };
//
//    virtual void init() {}
//    virtual void update(float mFT) {}
//    virtual void draw() {}
//
//    virtual ~Component() {}
//  };
//
//  // An aggregate of components
//  class Entity {
//  public:
//    void update(float mFT) { for (auto& c : _components) c->update(mFT); }
//    void draw() { for (auto& c : _components) c->draw(); }
//
//    bool isAlive() const { return _isAlive; }
//    void destroy() { _isAlive = false; }
//
//    template<typename T> bool hasComponent() const {
//      return ComponentBitset[getComponentId<T>()];
//    }
//
//    // T is type of derived componet to add 
//    // TArgs is a parameter pack to pass to component T's constructor 
//    template<typename T, typename ... TArgs>
//    T& addComponent(TArgs&&... mArgs) {
//      assert(!hasComponent<T>());
//
//      // Allocate component of type T perfectly forwarding passed args to its constructor.
//      T* c(new T(std::forward<TArgs>(mArgs)...));
//      c->entity = this; // Set component's parent entity
//      auto ptr = std::make_unique(c);
//      _components.emplace_back(std::move(ptr)); // move because unique cannot be copied
//
//      _componentArray[getComponentId<T>()] = c;
//      _componentBitset[getComponentId<T>()] = true;
//
//      c->init();
//
//      return *c; // return reference to the newly created component
//    }
//
//    template<typename T> T& getComponent() const {
//      assert(hasComponent<T>());
//      auto ptr(componentArray[getComponentId<T>()]);
//      return *static_cast<T*>(ptr); // cast to derived component type
//    }
//
//  private:
//    bool _isAlive{ true };
//
//    std::vector<std::unique_ptr<Component>> _components;
//
//    ComponentBitset _componentBitset;
//    // Component bitset (check if compoent has entity with simple bitwise AND):
//    // [ 0 0 0 0 0 1 0 0 1 ]
//    //             |     |
//    //             |     \_ Entity has component type #0 
//    //             \_______ Entity has component type #3
//
//    ComponentArray _componentArray;
//    // Component array (find components in constant time)
//    // [0] = Component type #0
//    // [1] = nullptr
//    // [2] = nullptr
//    // [3] = Component type #3
//  };
//
//  // An aggregate of entities
//  struct Manager {
//  public:
//    void update(float mFT) {
//      // Remove dead entities using erase-remove-if idiom
//      _entities.erase(
//        std::remove_if(_entities.begin(), _entities.end(),
//          [](const std::unique_ptr<Entity>& entity) { return !entity->isAlive(); }),
//        _entities.end()
//      );
//
//      for (auto& e : _entities) { e->update(mFT); }
//    }
//
//    void draw() { for (auto& e : _entities) { e->draw(); } }
//
//    Entity& addEntity() {
//      Entity* e( new Entity{});
//      std::unique_ptr<Entity> ptr{ e };
//      _entities.emplace_back(std::move(ptr));
//      return *e;
//    }
//
//  private:
//    std::vector<std::unique_ptr<Entity>> _entities;
//
//  };
//
//}
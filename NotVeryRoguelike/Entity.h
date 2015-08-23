#pragma once

#include "Component.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>
#include <assert.h>

namespace Game {

  enum Groups : std::size_t {
    PLAYER,
    NPC,
    MONSTER
  };

  using ComponentId = std::size_t; // Typedef
  using GroupId = std::size_t; // Typedef

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

    static ComponentId typeId{ getUniqueComponentId() }; // Init once per type T
    return typeId;
  }

  constexpr std::size_t MAX_COMPONENTS{ 32 };
  using ComponentBitset = std::bitset<MAX_COMPONENTS>; // Typedef
  using ComponentArray = std::array<Component*, MAX_COMPONENTS>; // Typedef

  constexpr std::size_t MAX_GROUPS{ 32 };
  using GroupBitset = std::bitset<MAX_GROUPS>; // Typedef

  class Manager; // foward declare

  // An aggregate of components
  class Entity {
  public:
    Entity(Manager& manager) : _manager(manager) {}

    void update(float mFT) { for (auto& c : _components) c->update(mFT); }
    void draw() { for (auto& c : _components) c->draw(); }

    bool isAlive() const { return _isAlive; }
    void destroy() { _isAlive = false; }

    template<typename T> bool hasComponent() const noexcept {
      return ComponentBitset[getComponentId<T>()];
    }

    // T is type of derived componet to add 
    // TArgs is a parameter pack to pass to component T's constructor 
    template<typename T, typename ... TArgs>
    T& addComponent(TArgs&&... mArgs) {
      assert(!hasComponent<T>());

      // Allocate component of type T perfectly forwarding passed args to its constructor.
      T* c(new T(std::forward<TArgs>(mArgs)...));
      c->entity = this; // Set component's parent entity
      auto ptr = std::make_unique(c);
      _components.emplace_back(std::move(ptr)); // move because unique cannot be copied

      _componentArray[getComponentId<T>()] = c;
      _componentBitset[getComponentId<T>()] = true;

      c->init();

      return *c; // return reference to the newly created component
    }

    template<typename T> T& getComponent() const {
      assert(hasComponent<T>());
      auto ptr(componentArray[getComponentId<T>()]);
      return *static_cast<T*>(ptr); // cast to derived component type
    }

    template<typename T> bool hasGroup(GroupId id) const noexcept {
      return GroupBitset[id];
    }

    void addGroup(GroupId id) noexcept {
      _groupBitset[id] = true;
      _manager.addToGroup(this, id);
    }

    void deleteGroup(GroupId groupId) noexcept {
      _groupBitset[groupId] = false;
    }

  private:
    Manager& _manager;

    bool _isAlive{ true };
    std::vector<std::unique_ptr<Component>> _components;

    // Component bitset (check if compoent has entity with simple bitwise AND):
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
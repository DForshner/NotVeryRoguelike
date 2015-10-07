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

#include <functional>
#include <algorithm>

namespace Game {

  // Position in the game world
  struct PositionComponent : Component {
    int x{ 0 };
    int y{ 0 };

    //PositionComponent() = default;
    PositionComponent(int x, int y) : x(x), y(y) {}

    ~PositionComponent() = default;
  };

  struct Dependant : Component {
    PositionComponent* _position{ nullptr }; // Requires a ph
    int _someValue;
    std::function<void(const int x, const int y)> _callback;

    Dependant(const int& someValue) : _someValue{ someValue } {}

    void init() override {
      _position = &entity->getComponent<PositionComponent>();
    }
  };

  struct InputComponent : Component {
    // void update() {} - Detect key press and update phsyics compoent velocty 
  };

  struct HealthComponent : Component {
    HealthComponent(int health, int maxHealth) : 
      health(health),
      maxHealth(maxHealth) 
    {}

    int health{ 0 };
    int maxHealth{ 0 };

    void setHealth(int h) { health = h; }
    void changeHealth(int delta) { 
      health += delta; 
      // if (health < 0) 
    }
  };

  struct StrengthComponent : Component {
    StrengthComponent(int str) : strength(str) {}
    int strength{ 0 };
  };

  struct SpeedComponent : Component {
    SpeedComponent(int spd) : speed(spd) {}
    int speed{ 0 };
  };

  struct ManaComponent : Component {
    int mana{ 0 };
    int maxMana{ 0 };

    void setMana(int m) { mana = m; }
  };

  struct RegenComponent : Component {
    float manaRestoreRate{ 0 };
    float healthRestoreRate{ 0 };
    HealthComponent* _healthComponent{ nullptr };
    ManaComponent* _manaComponent{ nullptr };

    RegenComponent(const int& healthRate, const int& manaRate) : healthRestoreRate(healthRate), manaRestoreRate(manaRate) {}

    void init() override {
      _healthComponent = &entity->getComponent<HealthComponent>();
      _manaComponent = &entity->getComponent<ManaComponent>();
    }

    void update(float dt) {
      // HealthPart healthPart = getEntity().get(HealthPart.class);
      float newHealth = calculateRestoredValue(_healthComponent->maxHealth, _healthComponent->health, healthRestoreRate * dt);
      _healthComponent->setHealth(newHealth);

      float newMana = calculateRestoredValue(_manaComponent->maxMana, _manaComponent->mana, manaRestoreRate * dt);
      _manaComponent->setMana(newMana);
    };

    float calculateRestoredValue(float maxValue, float currentValue, float restoreRate) {
      float manaRestoreAmount = maxValue * restoreRate;
      float maxManaRestoreAmount = min(maxValue - currentValue, manaRestoreAmount);
      return currentValue + maxManaRestoreAmount;
    }

  };

  struct EventPublisherComponent : Component {
    // eventsToPublish
    // update -> publish events
  };

  struct EventListenerComponent : Component {
    // eventsForEntity
    // update -> listen for events 
  };

  struct MonsterAIComponent : Component {
    void update(float dt) {
      // Do I have target
          // Am I near
             // Attack 
             // Move towards
          // Find nearby target
      // ...
    }
  };

  enum class Mentality {
    NONE,
    PLAYER,
    OFFENSIVE,
    SUPPORT,
    SUMMON
  };

  struct MentalityComponent : Component {
    Mentality mentality{ Mentality::NONE };
  };

  struct AllianceComponent : Component {
    int alliance{ 0 };
  };

  struct MagicSystem {
    // Summon example
    // EventPublisher.publish<EntityCreatedEvent>(args..);
  };

  struct Weapon {
    int damageType{ 1 };
    int range{ 1 };
    int value{ 2 };
  };

  struct Armour {
    int value{ 1 };
  };

  struct Spell {
    int value{ 1 };
  };

  struct EquipmentComponent : Component {
    Weapon equipedWeapon;
    Armour equipedArmour;
    Armour equipedSpell;
  };

  struct DistructableComponent : Component {
    bool isVulnerable(int damageType) { return true; }
  };

  struct NameComponent : Component {
    NameComponent(std::string n) : name(std::move(name)) {}

    std::string name;
  };

  struct DialogComponent : Component {
    DialogComponent(std::string m) : msg(std::move(m)) {}

    std::string msg;
  };

  struct TileComponent : Component {
    TileComponent(CHAR_INFO tile, bool isSolid) : 
      tile(tile), isSolid(isSolid) 
    {}

    CHAR_INFO tile;
    bool isSolid;
  };

}
#pragma once

#include "Component.h"
#include "PositionComponent.h"

#include <functional>
#include <algorithm>

namespace Game {

  struct Dependant : Component {
    PositionComponent* _position{ nullptr };
    int _someValue;
    std::function<void(const int x, const int y)> _callback;

    Dependant(const int& someValue) : _someValue{ someValue } {}

    void init() override {
      _position = &entity->getComponent<PositionComponent>();
    }
  };

  struct InputComponent : Component {
    // void update() {} - Detect key press and update physics component velocity 
  };

  struct StrengthComponent : Component {
    StrengthComponent(int str) : strength(str) {}
    int strength{ 0 };
  };

  struct SpeedComponent : Component {
    SpeedComponent(int spd) : speed(spd) {}
    int speed{ 0 };
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




}
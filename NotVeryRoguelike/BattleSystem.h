#pragma once

#include "PositionComponent.h"
#include "EntityManager.h"
#include "EventManager.h"

namespace Game {

  // Systems are where high-level interactions occur between entities.  Targeting, AI, etc.
  // Provides battle rules for game, damage, death etc.
  class BattleSystem {
  public:

    void update() {
      auto entities = _entityManager.getEntitiesByGroup(Groups::MONSTER);
      for (auto entity : entities) {
        if (!entity->isAlive()) { continue; }
        act(entity);
      }
    }

    void act(Entity* actor) {
      auto mentality = actor->getComponent<MentalityComponent>().mentality;
      switch (mentality) {
        case Mentality::NONE:
          break;
        case Mentality::OFFENSIVE:
          // attemptAttack;
          break;
      }
    }

    void attemptAttack(Entity* actor) {
      std::vector<Entity*> nearby; // TODO: Fill via spatial sys 

      for (auto target : nearby) {
        if (!target->isAlive()) { continue; }
        if (actor->getComponent<AllianceComponent>().alliance == target->getComponent<AllianceComponent>().alliance) { continue; }
        auto weapon = actor->getComponent<EquipmentComponent>().equipedWeapon;

        // Check if weapon can reach and can damage target
        auto distance = 5; // TODO: Get distance to target from spatial sys 
        if (weapon.range <= distance) { continue; }
        if (!target->getComponent<DistructableComponent>().isVulnerable(weapon.damageType)) { continue; }

        auto armour = actor->getComponent<EquipmentComponent>().equipedArmour;
        auto damage = weapon.value - armour.value;
        
        target->getComponent<HealthComponent>().changeHealth(-damage);
        break;
      }
    }

    void attemptHeal(Entity* actor) {

      auto mana = actor->getComponent<ManaComponent>();
    }

  private:
    EntityManager& _entityManager;
    EventManager* _eventManager;

  };

}

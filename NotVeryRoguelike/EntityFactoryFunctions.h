#pragma once

#include "Manager.h"
#include "Entity.h"
#include "PositionComponent.h"

namespace Game {

  Entity& createPlayer(Manager& manager) {
    auto& entity(manager.addEntity());

    entity.addComponent<PositionComponent>();
    entity.addComponent<Dependant>(10);
    auto& dep = entity.getComponent<Dependant>();
    dep._callback = [&dep](const int& test) { dep._someValue += test; };

    entity.addGroup(Groups::PLAYER);

    return entity;
  }

  //Entity& createNpc(Manager& manager) {

}
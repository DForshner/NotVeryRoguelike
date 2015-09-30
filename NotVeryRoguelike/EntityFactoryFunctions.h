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

#include "EntityManager.h"
#include "Entity.h"
#include "NullComponent.h"
#include "PositionComponent.h"

namespace Game {

  Entity& createNpc(EntityManager& manager, int x, int y, std::string name, std::string msg) {
    auto& entity(manager.addEntity());

    entity.addComponent(std::make_unique<PositionComponent>(x, y));
    entity.addComponent(std::make_unique<NameComponent>(name));
    entity.addComponent(std::make_unique<DialogComponent>(msg));

    //entity.addComponent<Dependant>(10);
    //auto& dep = entity.getComponent<Dependant>();
    //dep._callback = [&dep](const int& test) { dep._someValue += test; };

    entity.addGroup(Groups::NPC);

    return entity;
  }

  Entity& createMonster(EntityManager& manager, int x, int y) {
    auto& entity(manager.addEntity());

    entity.addComponent(std::make_unique<PositionComponent>(x, y));

    return entity;
  }
}
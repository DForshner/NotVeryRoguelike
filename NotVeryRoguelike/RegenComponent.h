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
#include "HealthComponent.h"
#include "ManaComponent.h"

#include <functional>
#include <algorithm>

namespace Game {

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

}
#pragma once

#include "Component.h"
#include <functional>

namespace Game {

  // Position in the game world
  struct PositionComponent : Component {
    int x{ 0 };
    int y{ 0 };


    PositionComponent() = default;
    PositionComponent(int x, int y) : x(x), y(y) {}
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

}
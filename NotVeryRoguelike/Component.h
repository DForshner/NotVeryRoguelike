
#pragma once

#include "Entity.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <array>
#include <assert.h>

namespace Game {

  class Entity; // Forward declaration

  struct Component {
    Entity* entity{ nullptr };

    virtual void init() {}
    virtual void update(float mFT) {}
    virtual void draw() {}

    virtual ~Component() {}
  };

}
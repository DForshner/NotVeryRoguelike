
#pragma once

#include <typeinfo>
#include <bitset>

namespace Game {

  using ComponentId = std::size_t; // Typedef
  constexpr std::size_t MAX_COMPONENTS{ 32 };
  using ComponentBitset = std::bitset<MAX_COMPONENTS>; // Typedef

  using GroupId = std::size_t; // Typedef
  constexpr std::size_t MAX_GROUPS{ 32 };
  using GroupBitset = std::bitset<MAX_GROUPS>; // Typedef

  enum Groups : std::size_t {
    PLAYER,
    NPC,
    MONSTER
  };

}
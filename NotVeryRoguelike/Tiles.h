/* Licensed to the Apache Software Foundation(ASF) under one
* or more contributor license agreements.See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.You may obtain a copy of the License at
*
* http ://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#pragma once

#include "Symbols.h"

#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <iterator>

namespace Game {

  enum class TileTypes {
    Tile = 0,
    Item,
    Monster,
    Npc,
    Exit
  };

  enum class Itemtypes {
    Item = 0,
    Head,
    Chest,
    Weapon,
    Feet
  };

  class Tile {
  public:

    Tile(Console::Position position, Console::Symbol image, bool isSolid) :
      _position(position), _image(image), _isSolid(isSolid) {}

    Console::Symbol getSymbol() const { return _image; }

    Console::Position getPosition() const { return _position; }

    bool isSolid() const { return _isSolid; }

  private:
    Console::Symbol _image;
    TileTypes _type;
    Console::Position _position;
    bool _isSolid;
  };

  class Item {
  public:
    Item() {}

  private:

  };

  class Monster {
  public:
    Monster() {}
  private:
  };

  class Npc {
  public:
    Npc() {}
    Npc(std::string name, std::string msg) : _name(name), _msg(msg) {}

    std::string getName() const { return _name; }
    std::string getMessage() const { return _msg; }

    friend std::ostream & operator<<(std::ostream & sout, const Npc& foo) {
      sout
        << "{\n"
          << "id: " << foo.id << "\n"
          << "name: " << std::quoted(foo._name) << "\n"
          << "msg: " << std::quoted(foo._msg) << "\n"
        << "},\n";
      return sout;
    }

    friend std::istream& operator>>(std::istream& sin, Npc& npc) {
      sin.ignore(5, '{');   // ignore until opening bracket 

      std::string chunk;
      while (chunk != "},") {
        sin >> chunk;
        if (chunk == "id:") { sin >> npc.id; }
        else if (chunk == "name:") { sin >> std::quoted(npc._name); }
        else if (chunk == "msg:") { sin >> std::quoted(npc._msg); }
      }
      return sin;
    }

  private:
    int id;
    std::string _name;
    std::string _msg;
  };

  class Exit {
  public:
    Exit(std::string mapName, Console::Position newPosition) :
      _mapName(mapName),
      _newPosition(newPosition)
    {}

    std::string getMapName() const { return _mapName; }
    Console::Position getDestination() const { return _newPosition; }

  private:
    std::string _mapName;
    Console::Position _newPosition;
  };

}
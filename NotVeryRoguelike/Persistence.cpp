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

#include "Persistence.h"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <assert.h>
#include <cctype>
#include <fstream>

namespace Game {

  void saveNpcs(const std::vector<Npc>& npcs) {
    std::ofstream out("/data/npcs.txt");
    auto units = 3;
    out << units;
    for (const auto& npc : npcs) {
      out << npc;
    }
    out.close();
  }

  std::vector<Npc> loadNpcs() {
    std::vector<Npc> ret;

    std::string filename{ "/data/npcs.txt"};
    std::ifstream in;
    in.exceptions(std::ios::failbit | std::ios::badbit);

    try {
      in.open(filename);

      int count = 0;
      in >> count;

      std::copy_n(std::istream_iterator<Npc>(in), count, std::back_inserter(ret));
    }
    catch (std::ios_base::failure &e) {
      throw std::exception(std::string("Could not open file : " + filename + " for reading. " + e.what()).c_str());
    }

    return ret;
  }

}
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

#include "World.h"
#include "Input.h" 
#include "Menu.h"
#include <chrono>

const int WIDTH2{ 80 };
const int HEIGHT2{ 45 };

typedef std::chrono::duration<long, std::ratio<1, 60>> sixtieths_of_a_sec;
typedef std::chrono::high_resolution_clock Clock;

int main()
{
  auto kMaxDeltatime = sixtieths_of_a_sec{ 1 };

  Console::init();

  Console::Input input;

  static std::vector<Event> toProcess;
  Game::Menu menu(WIDTH2, HEIGHT2);
  Game::World world;

  toProcess.emplace_back(Event{ EventTypes::REQUEST_MAP_REDRAW });

  auto lastEndTime = Clock::now();
  while (world.isPlayerAlive()) {

    auto newEndTime = Clock::now();
    auto frameTime = newEndTime - lastEndTime;
    lastEndTime = newEndTime;
    if (frameTime.count() == 0) { continue; }

    auto inputEvent = input.checkInput();
    if (inputEvent.type != EventTypes::NOOP) {
      toProcess.emplace_back(inputEvent);
    }

    world.updateNPCs();
      
    if (!toProcess.empty()) {
      auto menuEvents = menu.handleEvents(toProcess);
      auto worldEvents = world.handleEvents(toProcess);

      toProcess.clear(); // Clear handled events
      toProcess.reserve(menuEvents.size() + worldEvents.size());
      if (!menuEvents.empty()) { toProcess.insert(toProcess.end(), menuEvents.begin(), menuEvents.end()); }
      if (!worldEvents.empty()) { toProcess.insert(toProcess.end(), worldEvents.begin(), worldEvents.end()); }
    }
  }

	return 1;
}
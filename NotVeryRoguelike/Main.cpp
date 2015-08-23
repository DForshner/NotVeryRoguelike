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
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <assert.h>
#include <cctype>

const int WIDTH2{ 80 };
const int HEIGHT2{ 45 };

typedef std::chrono::duration<long, std::ratio<1, 60>> sixtieths_of_a_sec;
typedef std::chrono::high_resolution_clock Clock;

struct Foo {
  double  x;
  double  y;
  int id;
  std::string name;

  friend std::ostream & operator<<(std::ostream & sout, const Foo& foo) {
    sout << std::fixed << std::setprecision(15)
      << "{\n"
        << "x: " << foo.x << "\n"
        << "y: " << foo.y << "\n"
        << "id: " << foo.id << "\n"
        << "name: " << std::quoted(foo.name) << "\n"
      << "},\n";

    return sout;
  }

  friend std::istream& operator>>(std::istream& sin, Foo& foo) {
    sin.ignore(256, '{');   // ignore until opening bracket 

    std::string chunk;
    while (chunk != "},") {
      sin >> chunk;
      if (chunk == "x:") { sin >> foo.x; }
      else if (chunk == "y:") { sin >> foo.y; }
      else if (chunk == "id:") { sin >> foo.id; }
      else if (chunk == "name:") { sin >> std::quoted(foo.name); }
    }
      
    //auto test5 = sin.peek();
    //sin.ignore(5, '\n');
    //auto test = sin.peek();
    //if (isspace(sin.peek())) {
    //}

    //if (sin.peek() == std::char_traits<char>::eof()) {
      //sin.();
    //}

    //while (isspace(sin.peek())) {
      //auto test3 = sin.peek();
      //sin.ignore(1);
    //}
    auto test2 = sin.peek();

    //while (isspace(sin.peek()) || iscntrl(sin.peek())) {
      //sin.ignore(1);
    //}

    //if (sin.peek() == std::char_traits<char>::eof()) {
      //auto test = sin.peek();
    //}

    return sin;
  }

};

int main() {
  auto kMaxDeltatime = sixtieths_of_a_sec{ 1 };

  Foo foo{ 1.2, 3.4, 3, "My name is Tom." };

  std::ofstream out("output.txt");
  auto units = 3;
  out << units;
  for (auto i = 0; i < units ; ++i) {
    foo.id = i;
    out << foo;
  }
  out.close();

  std::string filename{ "output.txt"};
  std::ifstream in;
  in.exceptions(std::ios::failbit | std::ios::badbit);

  std::vector<Foo> myFoos;
  try {
    in.open(filename);

    int count = 0;
    in >> count;

    std::copy_n(std::istream_iterator<Foo>(in), count, std::back_inserter(myFoos));
  }

  catch (std::ios_base::failure &e) {
    //std::cerr << e.what() << "\n";
    throw std::exception(std::string("Could not open file : " + filename + " for reading. " + e.what()).c_str());
  }

  //std::istream_iterator<Foo> eof;
  //std::istream_iterator<Foo> sin{ in };
  //auto count = 0;
  //if (sin != eof) {
    //sin >> count;
    //sin++;

  //std::copy_n(std::istream_iterator<Foo>(in), std::istream_iterator<Foo>(), std::back_inserter(myFoos));

  auto test = myFoos.back();

  //while (sin != eof) {
    //auto bar = *sin;
    //std::cout << bar.name << " " << bar.id << std::endl;
    //++sin;
  //}

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
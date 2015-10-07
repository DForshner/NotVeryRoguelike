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

#include "Console.h"

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <conio.h>
#include <assert.h>

namespace Console {

  const int WIDTH{ 80 };
  const int HEIGHT{ 45 };

  // This is our screen buffer that holds the color ASCII characters
  CHAR_INFO consoleBuffer[WIDTH * HEIGHT];

  void init() {
    SetConsoleTitle("Not Very Rogue Like");

    // Set window size
    SMALL_RECT newSize{ 0, 0, WIDTH - 1, HEIGHT - 1 };
    auto outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(outputHandle, TRUE, &newSize);

    // Change the internal buffer size:
    COORD bufferSize = { WIDTH, HEIGHT };
    SetConsoleScreenBufferSize(outputHandle, bufferSize);
  }

  // Adds the background tile's color to the foreground tile.
  CHAR_INFO addNewBackground(CHAR_INFO fore, CHAR_INFO back) {

    // Clear the foregrounds's background
    constexpr unsigned FOREGROUND_MASK = 0x000F;
    fore.Attributes &= FOREGROUND_MASK;

    // Clear the background's foreground
    constexpr unsigned BACKGROUND_MASK = 0xFFF0;
    back.Attributes &= BACKGROUND_MASK;

    // Combine the foreground's foreground with the background's background
    fore.Attributes |= back.Attributes;

    return fore;
  }

  void draw(const Symbol& symbol, const Position& position) {
    DWORD dwResult = 0;

    char toDraw[2]{ static_cast<char>(symbol.Char.Char.AsciiChar) };
    auto outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleOutputCharacter(outputHandle, toDraw, 1, position.getCoord(), &dwResult);

    WriteConsoleOutputAttribute(outputHandle, &symbol.Char.Attributes, 1, position.getCoord(), &dwResult);
  }

  void drawTiles(
    const std::vector<Game::Tile>& background,
    const std::vector<std::vector<Game::Tile>*>& foreground
    , int width, int height) {

    // Here we go through our normal map tile list and add them to our drawing screen buffer
    for (int i = 0; i < background.size(); i++) {
      consoleBuffer[i] = background[i].getSymbol().Char;
    }

    for (const auto& typeTiles : foreground) {
      for (const auto& tile : *typeTiles) {
        auto pos = tile.getPosition();
        int slot = pos.X + pos.Y * width;
        auto background = consoleBuffer[slot];
        auto layered = addNewBackground(tile.getSymbol().Char, background);
        consoleBuffer[slot] = layered;
      }
    }

    // Draw buffer we just populated to the screen.
    auto outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize{ width , height };
    COORD zeroZeroStart{ 0, 0 }; // Start from upper left corner 
    SMALL_RECT writeArea{ 0, 0, width - 1, height - 1 };
    WriteConsoleOutput(outputHandle, consoleBuffer, bufferSize, zeroZeroStart, &writeArea);
  }

  constexpr int LINE_LENGTH = 52;

  void displayDialog(std::string name, std::string dialog) {
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwResult = 0;

    WORD dialogColor =
      FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | // White 
      BACKGROUND_BLUE | BACKGROUND_INTENSITY; // Intense Blue

    int dialogLines = dialog.size() / LINE_LENGTH;

    // We will start the dialog text at the screens coordinates (13, 13).
    COORD dlgPosition = { 13, 13 };

    // Draw box starting at 10,10
    //g_Menu.DrawBox(LINE_LENGTH + 6, dialogLines + 6, 10, 10);

  }

  void waitForKey() {
    // Flush input buffer so player has chance to hit a key.
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    getch();
  }

  void drawString(int x, int y, const std::string& s, const Color& color) {
    assert(x >= 0 && x <= WIDTH);
    assert(y >= 0 && x <= HEIGHT);

    auto output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD result{ 0 };
    COORD pos{ x, y };

    const char* str = s.c_str();
    auto length = min(s.length(), WIDTH - x); // Don't write over edge of screen

    WriteConsoleOutputCharacter(output, str, length, pos, &result);
    FillConsoleOutputAttribute(output, color.Attribute, length, pos, &result);
  }

  constexpr int MIN_BOX_DIM = 2;
  constexpr char HORIZONTAL = 0xCD;
  constexpr char TOP_LEFT = 0xC9;
  constexpr char TOP_RIGHT = 0xBB;
  constexpr char VERTICAL = 0xBA;
  constexpr char BOTTOM_LEFT = 0xC8;
  constexpr char BOTTOM_RIGHT = 0xBC;
  constexpr char EMPTY = 0x20;

  void drawBox(int width, int height, int x, int y) {
    assert(x >= 0 && x <= WIDTH);
    assert(width + x <= WIDTH);
    assert(y >= 0 && x <= HEIGHT);
    assert(height + y <= HEIGHT);
    assert(width >= MIN_BOX_DIM);
    assert(height >= MIN_BOX_DIM);

    std::string top(static_cast<size_t>(width), HORIZONTAL);
    top[0] = TOP_LEFT;
    top[width - 1] = TOP_RIGHT;
    drawString(x, y, top, TEXT_COLOR);

    std::string bottom(top);
    bottom[0] = BOTTOM_LEFT;
    bottom[width - 1] = BOTTOM_RIGHT;
    drawString(x, y + (height - 1), bottom, TEXT_COLOR);

    std::string mid(static_cast<size_t>(width), EMPTY);
    mid[0] = VERTICAL;
    mid[width - 1] = VERTICAL;
    for (auto i = 1; i < (height - 1); ++i) {
      drawString(x, y + i, mid, TEXT_COLOR);
    }
  }


}
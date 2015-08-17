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

#include "Input.h"

// See: http://www.benryves.com/tutorials/winconsole/3
// TODO: Implement map creation

namespace Console {

  Input::Input() {
    memset(&m_inputRecord, 0, sizeof(INPUT_RECORD));

    // Setup keaboard & mouse input
    auto inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(inputHandle, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
  }

  inline DWORD getNumberOfEvents(const HANDLE& inputHandle) {
    DWORD numEvents = 0;
    GetNumberOfConsoleInputEvents(inputHandle, &numEvents);
    return numEvents;
  }

  // Returns: true if there was user input
  Event Input::checkInput() {
    auto inputHandle = GetStdHandle(STD_INPUT_HANDLE);

    auto numEvents = getNumberOfEvents(inputHandle);
    if (!numEvents) { return Event{ EventTypes::NOOP }; }

    // If there was input, read what the user did and store it in m_inputRecord
    constexpr int READ_SINGLE_EVENT = 1;
    ReadConsoleInput(inputHandle, &m_inputRecord, READ_SINGLE_EVENT, &numEvents);

    // Ignore key up events
    bool isKeyDown = m_inputRecord.Event.KeyEvent.bKeyDown;
    if (!isKeyDown) { return Event{ EventTypes::NOOP }; }

    if (m_inputRecord.EventType == KEY_EVENT) {
      auto keyCode = m_inputRecord.Event.KeyEvent.wVirtualKeyCode;

      switch (keyCode) {
        case VK_ESCAPE:
          return Event{ EventTypes::ESCAPE };
        case VK_UP:
          return Event{ EventTypes::UP };
        case VK_DOWN:
          return Event{ EventTypes::DOWN };
        case VK_LEFT:
          return Event{ EventTypes::LEFT };
        case VK_RIGHT:
          return Event{ EventTypes::RIGHT };
        case VK_SPACE:
          return Event{ EventTypes::SPACE };
      }
    } else if (m_inputRecord.EventType == MOUSE_EVENT) {

      auto currPos = m_inputRecord.Event.MouseEvent.dwMousePosition;
      if (currPos.X != lastMousePosition.X || currPos.Y != lastMousePosition.Y) {
        return Event{ EventTypes::MOUSE_MOVE };
      }

      auto buttonState = m_inputRecord.Event.MouseEvent.dwButtonState;
      switch (buttonState) {
        case FROM_LEFT_1ST_BUTTON_PRESSED:
          return Event{ EventTypes::LEFT };
        case RIGHTMOST_BUTTON_PRESSED:
          return Event{ EventTypes::RIGHT };
      }
    }

    return Event{ EventTypes::NOOP };
  }
}
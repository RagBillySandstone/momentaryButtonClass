// Copyright 2018 Stephen Castaneda
// stephen.c976@gmail.com

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BUTTON_H
#define BUTTON_H

// BYTE... no more than a quarter second!!!
#define DEBOUNCE_THRESHOLD 40
// This one's an unsigned int - go nuts
#define DOUBLE_CLICK_THRESHOLD 1000

#include "Arduino.h"

class Button {
  public:
    Button();
    void begin(byte pinNumber,
              byte debounceThreshold = DEBOUNCE_THRESHOLD,
              unsigned int doubleClickThreshold = DOUBLE_CLICK_THRESHOLD);
    bool debouncedRead();
      // Use in place of digitalRead() for debounced input
    bool readSingleClick();
      // true if ( _isSingleClicked && DOUBLE_CLICK_THRESHOLD is expired )
      // Clears "single click" and "double click" if true
    bool readDoubleClick();
      // true if ( _isSingleClicked && !(DOUBLE_CLICK_THRESHOLD is expired))
      // Clears "double click" if true

  private:
    byte _pin;
    byte _debounceThreshold = DEBOUNCE_THRESHOLD;
    unsigned long _lastDebounceTime = 0;
    bool _lastDebouncedState = LOW;

    unsigned int _doubleClickThreshold = DOUBLE_CLICK_THRESHOLD;
    unsigned long _lastClickTime = 0;
    bool _isSingleClicked = false;
    bool _isDoubleClicked = false;
    unsigned long _now; // For functions to save current millis()

    void _registerClick(unsigned long clickTime);
    void _checkDoubleClick(unsigned long clickTime);

};

#endif

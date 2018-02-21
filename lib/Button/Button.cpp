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

#include "Arduino.h"
#include "Button.h"

Button::Button() {
  _lastDebounceTime = 0;
  _lastDebouncedState = digitalRead(_pin);
}

void Button::begin(byte pinNumber) {
  _pin = pinNumber;
}

bool Button::debouncedRead() {
  // Use in place of digitalRead() for debounced read on this pin
  _now = millis();

  // TODO: check PIN register instead of doing:
  int currentReading = digitalRead(_pin);
  if (currentReading != _lastDebouncedState) {
    _lastDebounceTime = _now; // reset the timer
  }

  // Check if the input passes the debounce
  // but don't do anything unless the state changed:
  if ( (_now - _lastDebounceTime) > _debounceThreshold){
    bool didStateChange = (currentReading != _lastDebouncedState);
    if (didStateChange) {
      _lastDebouncedState = currentReading; // Change the state
      // Was there a "click?" i.e., did state change from high to low
      if (_lastDebouncedState == LOW)
        _registerClick(_now);
      } // end (didStateChange)
    } // end debounce check
  return _lastDebouncedState; // after all, that's what we asked for
}

void Button::_registerClick(unsigned long clickTime) {
  if (_isSingleClicked == true){
    _checkDoubleClick(clickTime);
  }
  else {
    _isSingleClicked = true;
    _lastClickTime = clickTime;
  }
}

void Button::_checkDoubleClick(unsigned long clickTime) {
  // There's been a "click" event while _isSingleClicked == true.
  // If the DOUBLE_CLICK_THRESHOLD hasn't expired, we have a "double click"
  bool isUnderThreshold = (clickTime - _lastClickTime <= _doubleClickThreshold);

  if (isUnderThreshold) {
    _isDoubleClicked = true;
    _isSingleClicked = false;
    _lastClickTime = 0;     // Forget there ever was a click
  }
  else {                    // Just the next "single click"
    _isDoubleClicked = false;
    _isSingleClicked = true;
    _lastClickTime = _now;
  }
}


bool Button::readSingleClick() {
  if (_isSingleClicked) {
    _isSingleClicked = false;

  }
    return _isSingleClicked;
}

bool Button::readDoubleClick() {
    return LOW;
}

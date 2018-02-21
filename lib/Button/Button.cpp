#include "Arduino.h"
#include "Button.h"

Button::Button() {
  _lastDebounceTime = 0;
  _lastDebouncedState = digitalRead(_pin);
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
  _now = millis();
  bool isUnderThreshold = (_now - _lastClickTime <= _doubleClickThreshold);

  if (isUnderThreshold) {   // We have a "double click"
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

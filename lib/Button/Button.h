/* Library for user input from a standard normally open momentary button
  Offers a debounced digital read and read for "click" and "double click"
  Steve Castaneda, Stephen.C976@gmail.com
  Feb 18, 2018
*/

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
    bool debouncedRead();
      // Use in place of digitalRead() for debounced input
    bool readSingleClick();
      // true if ( _isSingleClicked && DOUBLE_CLICK_THRESHOLD is expired )
      // Clears "single click" if true
    bool readDoubleClick();
      // true if ( _isSingleClicked && !(DOUBLE_CLICK_THRESHOLD is expired))
      // Clears "double click" if true

  private:
    byte _pin;
    const byte _debounceThreshold = DEBOUNCE_THRESHOLD;
    unsigned long _lastDebounceTime = 0;
    bool _lastDebouncedState = LOW;

    const unsigned int _doubleClickThreshold = DOUBLE_CLICK_THRESHOLD;
    unsigned long _lastClickTime = 0;
    bool _isSingleClicked = false;
    bool _isDoubleClicked = false;
    unsigned long _now; // For functions to save current millis()

    void _registerClick(unsigned long clickTime);
    void _checkDoubleClick(unsigned long clickTime);

};

#endif

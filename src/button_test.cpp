#include <../lib/Button/Button.h>

Button thisButt;

void setup() {
  Serial.begin(9600);
}

void loop() {
  bool reading1 = thisButt.debouncedRead();
  Serial.println(reading1);
  delay(333);
}

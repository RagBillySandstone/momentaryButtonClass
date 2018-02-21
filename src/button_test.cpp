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


/* We want to test the debounce most of all. The main loop should count the
    number of times the actual input changes before debounced input changes.
    and then hopefully give us some stats about it
*/


#include <Button.h>
#define BUTTON_1 12


Button thisButton;

// TODO: Not constants so I can implement a function to tune them later
byte debounceThreshold = 50;
unsigned int doubleClickThreshold = 1000;

bool lastDebounceState = LOW;
bool lastDigitalReadState = LOW;
unsigned int changesSinceDebounce = 0;

// For calculating average bounces per debounce
unsigned int totalBounces = 0;
unsigned int totalDebouncedChanges = 0;

// For timing our bounce/debounce report period
unsigned long now = 0;
unsigned long lastSummary = 0;
unsigned int summaryInterval = 10000;


void setup() {
  Serial.begin(9600);
  thisButton.begin(BUTTON_1, debounceThreshold, doubleClickThreshold);
}


void loop() {
  now = millis();
  if (thisButton.debouncedRead() != lastDebounceState) {
    lastDebounceState = !lastDebounceState;
    Serial.print("Debounced input detected. ");
    Serial.print(changesSinceDebounce);
    Serial.print(" bounces since last debounced change.\n");

    totalBounces += changesSinceDebounce;
    totalDebouncedChanges +=1;
    changesSinceDebounce = 0;
  }

  if (digitalRead(BUTTON_1) != lastDigitalReadState) {
    lastDigitalReadState = !lastDigitalReadState;
    changesSinceDebounce += 1;
    Serial.print("Bounce detected\n");
  }

  if (now - lastSummary >= summaryInterval) {
    double average = double(totalBounces) / double(totalDebouncedChanges);
    Serial.print("Total bounces: ");
    Serial.print(totalBounces);
    Serial.print("   Total debounced: ");
    Serial.print(totalDebouncedChanges);
    Serial.println();
    Serial.print("Average: ");
    Serial.print(average);
    Serial.print(" bounces per debounced change.\n");
    Serial.println();
    lastSummary = now;
  }
}

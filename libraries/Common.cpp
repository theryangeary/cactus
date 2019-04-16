/*
 * Common.cpp - Library of common code used by both client and server feet
 */

#include "Arduino.h"
#include "Common.h"

// false is up, true is down
bool STATE = true;
int CHEAT_END_TIME;

void test() {
  Serial.println("this the the test; it works!");
  return;
}

int calibrate(int *calibrationValue) {
  // TODO
  return 1;
}

void setCheatEndTime() {
  CHEAT_END_TIME = millis() + CHEAT_LENGTH;
}

int getCheatEndTime() {
  return CHEAT_END_TIME;
}

bool cheating(int sem) {
  if (sem < 0) {
    setCheatEndTime();
    Serial.println("Cheating detected");
  }
}

bool footDown() {
  return true;
}

bool footUp() {
  return !footDown();
}

bool getCurrentState() {
  return footDown();
}

bool getPreviousState() {
  return STATE;
}

bool checkStateChange() {
  return getPreviousState() != getCurrentState();
}

void updateState() {
  STATE = getCurrentState();
}

bool startBuzz() {

}

bool stopBuzz() {

}

bool checkBuzzEnd() {

}


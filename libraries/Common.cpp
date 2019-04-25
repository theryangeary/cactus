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
  if (sem < 1) {
    setCheatEndTime();
    Serial.println("Cheating detected");
  }
}

bool footDown() {
  if (getVoltage() <= VOLT_THRESH) {
    return true;
  }
  else {
    return false;
  }
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

	ledcWriteTone(channel, freq);

}

bool stopBuzz() {

	ledcWriteTone(channel, 0);
}

bool checkBuzzEnd() {

}

float getVoltage() {

	float pinVal = (float) analogRead(FOOT_PIN);
	float oldMax = 4095.0;
	float oldMin = 0.0;
	float newMax = 3.3;
	float newMin = 0.0;
	float oldRange = oldMax - oldMin;
	float newRange = newMax - newMin;

	return (((pinVal - oldMin) * newRange) / oldRange) + newMin;

}

/*
 * Common.cpp - Library of common code used by both client and server feet
 */

#include "Arduino.h"
#include "Common.h"

// false is up, true is down
bool STATE = true;
int CHEAT_END_TIME;
int CALIBRATION_VALUE;

void test() {
  Serial.println("this the the test; it works!");
  return;
}

int calibrate() {
  CALIBRATION_VALUE = 1000;
  return 0;
}

void setCheatEndTime() {
  CHEAT_END_TIME = millis() + CHEAT_LENGTH;
}

int getCheatEndTime() {
  return CHEAT_END_TIME;
}

bool cheating(int sem) {
  if ((sem <<6 >>6)== 0) {
    setCheatEndTime();
    Serial.println("Cheating detected");
  }
}

bool footDown() {
  if (analogRead(FOOT_PIN) < CALIBRATION_VALUE + (0.1*CALIBRATION_VALUE)) {
    return false;
  }
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
  //ledcWrite(CHANNEL, 200);
  digitalWrite(BUZZER, HIGH);
}

bool stopBuzz() {
  //ledcWrite(CHANNEL, 0);
  digitalWrite(BUZZER, LOW);
}

bool checkBuzzEnd() {

}

int getCalibrationValue() {
  return CALIBRATION_VALUE;
}

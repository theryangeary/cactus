/*
 * Common.h - Library of common code used by both client and server feet
 */

#ifndef Common_h
#define Common_h

#include "Arduino.h"


#define CHEAT_LENGTH 2000
#define FOOT_PIN 35
#define BUZZER 32
#define VOLT_THRESH 2.4

#define FREQ 1000
#define CHANNEL 0
#define RESOLUTION 8

void test();
int calibrate(int *calibrationValue);
void setCheatEndTime();
int getCheatEndTime();
bool footDown();
bool footUp();
bool getCurrentState();
bool getPreviousState();
void updateState();
bool checkStateChange();
bool cheating(int sem);
bool startBuzz();
bool stopBuzz();
bool checkBuzzEnd();
float getVoltage();

#endif

/*
 * Common.h - Library of common code used by both client and server feet
 */

#ifndef Common_h
#define Common_h

#include "Arduino.h"


#define CHEAT_LENGTH 2000;


void test();
int calibrate(int *calibrationValue);
void setCheatEndTime();
int getCheatEndTime();
bool footDown();
bool footUp();
bool getCurrentState();
bool getPreviousState();
void updateState();
bool checkStateChange(bool previous);
bool cheating(int sem);
bool startBuzz();
bool stopBuzz();
bool checkBuzzEnd();

#endif

#include "libraries/CactusdBLE.h"
#include "libraries/Common.h"
#include <BLEDevice.h>
#include <string>

#define CHEAT_BUZZ_LENGTH 2000

int CHEAT_START_TIME = 0;
BLEConnection* conn = NULL;
int i = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
  pinMode(FOOT_PIN, OUTPUT);
  if ( 0 != calibrate() ) {
    Serial.println("Calibration failed");
  }

  //Initialize Bluetooth connection
  conn = new BLEConnection;
  Serial.println(conn->getStatus());
  updateState();
}


void loop() {
  if (checkStateChange()) {
    // check if this foot is up and if so decrement semaphore
    if (footUp()) {
      conn->semDec();
      Serial.println("UP");
    }
    // if foot is down then increment semaphore
    if (footDown()) {
      conn->semInc();
      Serial.println("DOWN");
    }
    updateState();
  }

  if (millis() < getCheatEndTime()) {
    startBuzz();
  } else {
    stopBuzz();
  }

  Serial.print("The characteristic value was: " );
  Serial.print(conn->characteristic->readValue().c_str());
  Serial.print(", Calibration value is: ");
  Serial.print(getCalibrationValue());
  Serial.print(", Current Value is: ");
  Serial.println(analogRead(FOOT_PIN));
  /*Serial.println(analogRead(35));*/
}

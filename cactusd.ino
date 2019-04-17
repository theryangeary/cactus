#include "libraries/CactusdBLE.h"
#include "libraries/Common.h"
#include <BLEDevice.h>
#include <string>

#define CHEAT_BUZZ_LENGTH 2000

int CHEAT_START_TIME = 0;
int CALIBRATION_VALUE = 0;
BLEConnection* conn = NULL;
int i = 0;

void setup() {
  Serial.begin(115200);

  if ( 0 != calibrate(&CALIBRATION_VALUE) ) {
    Serial.println("Calibration failed");
  }

  // Initialize Bluetooth connection
  conn = new BLEConnection;
  Serial.println(conn->getStatus());
}

void loop() {
  if (checkStateChange()) {
    // check if this foot is up and if so decrement semaphore
    if (footUp()) {
      conn->semDec();
    }
    // if foot is down then increment semaphore
    if (footDown()) {
      conn->semInc();
    }
  }

  updateState();

  if (millis() < getCheatEndTime()) {
    startBuzz();
  } else {
    stopBuzz();
  }

  Serial.print("The characteristic value was: " );
  Serial.println(conn->characteristic->readValue().c_str());
  delay(1000);
}

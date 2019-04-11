#include "libraries/Common.h"
#include "libraries/CactusdBLE.h"
#include <BLEDevice.h>
#include <string>

#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

#define CHEAT_BUZZ_LENGTH 2000

int CHEAT_START_TIME = 0;
int CALIBRATION_VALUE = 0;
BLEConnection* conn = NULL;

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
#ifdef CLIENT
  Serial.println(conn->getStatus());

  std::string value = "Time since boot: ";// + millis()/1000;

  Serial.println(value.c_str());

  conn->writeCharacteristic(CHARACTERISTIC_UUID, value);

#else
#endif

  Serial.print("The characteristic value was: " );
  Serial.println(conn->readCharacteristic(CHARACTERISTIC_UUID).c_str());
  delay(1000);
}

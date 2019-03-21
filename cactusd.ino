#include "libraries/Common.h"
#include "libraries/CactusdBLE.h"
#include <BLEDevice.h>

#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

#define CHEAT_BUZZ_LENGTH 2000

int CHEAT_START_TIME = 0;

void setup() {
  Serial.begin(115200);
  // Initialize Bluetooth connection
  initializeBLE();
}

void loop() {
  delay(1000);
}

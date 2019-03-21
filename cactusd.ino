#include "libraries/Common.h"
#include "libraries/CactusdBLE.h"
#include <BLEDevice.h>

#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

#define CHEAT_BUZZ_LENGTH 2000

int incoming;

void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  initializeBLE();
}

// the loop function runs over and over again forever
void loop() {
  delay(1000);
}

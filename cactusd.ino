#include "libraries/Common.h"
#include "BluetoothSerial.h"

#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

#define LED 2

BluetoothSerial ESP_BT;

int incoming;

void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  ESP_BT.begin("ESP32_BT");
}

// the loop function runs over and over again forever
void loop() {
  ESP_BT.println("connected");
  if (ESP_BT.available()) {
    incoming = ESP_BT.read();
    Serial.println(incoming);
  }
  delay(100);
}

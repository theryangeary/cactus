#include "libraries/Common.h"

#define LED 2

void setup() {
  // initialize digital pin LED as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
#ifdef SERVER
  Serial.println("Anna");
#endif
#ifdef CLIENT
  Serial.println("Ryan");
#endif
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

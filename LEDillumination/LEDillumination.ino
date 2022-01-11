#include "SerialLedController.h"
LedController led(13, 20, 1000, 50, 20);

void setup() {
  Serial.begin(115200);
}

void loop() {
  led.show();
}

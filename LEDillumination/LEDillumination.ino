#include "SerialLedController.h"
LedController led(13, 100, 5000, 50, 20);

void setup() {
  Serial.begin(115200);
}

void loop() {
  led.show();
}

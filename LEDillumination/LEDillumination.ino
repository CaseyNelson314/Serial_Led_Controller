#include "SerialLedController.h"
LedController led(13, 100, 1000, 50 ,20);
//遅延0.7ms/led

void setup() {
}

void loop() {
  led.showWave();
}

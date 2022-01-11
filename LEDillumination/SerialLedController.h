#pragma once
#include <Adafruit_NeoPixel.h>

class LedController {

  private:
    Adafruit_NeoPixel* serialLed;
    int8_t pin;
    int ledNum;
    int cycle;
    int8_t maxPower;
    int ledGroups;

    unsigned long time, lastTime;
    bool direction = 1;

  public:
    LedController(int8_t pin, int ledNum, int cycle, int8_t maxPower, int ledGroups):
      pin(pin), ledNum(ledNum), cycle(cycle), maxPower(maxPower), ledGroups(ledGroups) {
      serialLed = new Adafruit_NeoPixel(ledNum, pin);
      serialLed->begin();
    }
    ~LedController() {
      serialLed->~Adafruit_NeoPixel();
    }

    /*1つのLEDの色相が1周する周期(ms)*/
    void setCycle(int cycle) {
      this->cycle = cycle;
    }

    /*色相が1周するLEDのまとまりの合計*/
    void setGroups(int ledGroups) {
      this->ledGroups = ledGroups;
    }

    /*最高輝度(0~255)*/
    void setBrightness(int8_t maxPower) {
      this->maxPower = maxPower;
    }

    /*流れる方向(1:データ転送方向と同じ方向 0:逆)*/
    void setDirection(bool direction) {
      this->direction = direction;
    }

    void show() {
      /*error*/
      if (!cycle || !ledGroups)
        return;

      if ((time = millis()) - lastTime > cycle)lastTime = time;
      for (int j = 0; j < ledNum; j++) {
        int8_t outData[3];
        float nowTime = (float)(time - lastTime) * 2 / cycle - (direction ? 1 : -1) * ((float)j * 2 / ledGroups); //sin波出力用のx軸
        for (int i = 0; i < 3; i++)
          outData[i] = maxPower * (sin(fmod(nowTime - (float)i * 2 / 3, 2) * PI) + 1) / 2;
        serialLed->setPixelColor(j, outData[0], outData[1], outData[2]);
      }
      serialLed->show();
    }
};

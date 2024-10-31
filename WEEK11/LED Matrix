#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint32_t W[3] = {0x26426426, 0x42642642, 0x9430C204};
uint32_t I[3] = {0x3FC06006, 0x00600600, 0x600603FC};
uint32_t N[3] = {0x20430428, 0x42442242, 0x1420C204};

void setup() {
  matrix.begin();
}

void loop() {
  int interval = 1000;

  matrix.loadFrame(W);
  delay(interval);
  matrix.loadFrame(I);
  delay(interval);
  matrix.loadFrame(N);
  delay(interval);
}

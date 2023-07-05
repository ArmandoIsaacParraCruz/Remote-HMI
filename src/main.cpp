#include <Arduino.h>
#include "HMI.h"

HMI hmi{};

void setup() {
  Serial.begin(115200);
}

void loop() {
  hmi.HMI_main_loop();
}


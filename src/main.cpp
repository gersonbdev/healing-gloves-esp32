#include <Arduino.h>
#include "healg_definitions.h"

void setup() {
        Serial.begin(9600);
}

void loop() {
        Serial.println(touchRead(15));
        delay(100);
}
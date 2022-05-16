#include <Arduino.h>
#include <BluetoothSerial.h>

#include "healg_definitions.hpp"
#include "healg_sensor_communic_tasks.hpp"

BluetoothSerial SerialBT;

void setup()
{
        Serial.begin(115200);
        SerialBT.begin("HealingGloves");
}


void loop()
{
        keystrokes_task();
        rotations_task();
        communication_task();
        delay(100);
}

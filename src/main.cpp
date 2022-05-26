#include <Arduino.h>
#include <BluetoothSerial.h>

#include "healg_definitions.hpp"
#include "healg_tasks.hpp"
#include "communic_utilities.hpp"

BluetoothSerial SerialBT;

void setup()
{
        Serial.begin(115200);
        SerialBT.begin("HealingGloves");
}


void loop()
{   
        communication_task();

        delay(100);
}

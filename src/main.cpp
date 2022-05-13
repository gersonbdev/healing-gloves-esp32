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
        mpr121_communic_task();
        capacitive_communic_task();
        mpu6050_communic_task();

        delay(10);
}

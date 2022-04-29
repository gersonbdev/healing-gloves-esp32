#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "healg_sensor_functions.hpp"
#include "healg_sensor_tasks.hpp"

BluetoothSerial SerialBT;

void setup()
{
        Serial.begin(115200);
        SerialBT.begin("HealingGlovesRigth");
        // xTaskCreate(
        //         mpr121_task,
        //         "MPR121 task",
        //         2000,
        //         NULL,
        //         1,
        //         NULL
        // );

        // xTaskCreate(
        //         mpu6050_task,
        //         "MPU6050 task",
        //         2000,
        //         NULL,
        //         1,
        //         NULL
        // );   
}


void loop()
{
        mpr121_task();
}

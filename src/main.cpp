#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

#include "healg_definitions.hpp"
#include "healg_sensor_tasks.hpp"


void setup()
{
        Serial.begin(9600);  

        xTaskCreate(
                mpr121_task,
                "MPR121 task",
                2000,
                NULL,
                1,
                NULL
        );      
}


void loop()
{

}
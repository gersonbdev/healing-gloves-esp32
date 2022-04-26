#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "healg_sensor_functions.hpp"
#include "healg_sensor_tasks.hpp"

void mpr121_task(void * pvParameters)
{        
        Adafruit_MPR121 mpr121_sensor = Adafruit_MPR121();
        boolean mpr121_status = false;

        // Keeps track of the last pins touched
        // so we know when buttons are 'released'11
        uint16_t lasttouched = 0;
        uint16_t currtouched = 0;
        
        mpr121_status = set_mpr121_initialization(&mpr121_sensor, 0x5A);

        while (1) {                
                if (mpr121_status) {
                        Serial.println();
                        Serial.println("\t --- Begin --- ");
                        Serial.println();
                        // Get the currently touched pads
                        currtouched = mpr121_sensor.touched();

                        Serial.println(currtouched);

                        for (uint8_t i=0; i<12; i++) {
                        // it if *is* touched and *wasnt* touched before, alert!
                        if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
                        Serial.print(i); Serial.println(" touched");
                        }
                        // if it *was* touched and now *isnt*, alert!
                        if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
                        Serial.print(i); Serial.println(" released");
                        }
                        }

                        // reset our state
                        lasttouched = currtouched;

                        //delay(200);

                        // comment out this line for detailed data from the sensor!
                        //return;

                        // debugging info, what
                        Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(mpr121_sensor.touched(), HEX);
                        Serial.print("Filt: ");
                        for (uint8_t i=0; i<12; i++) {
                        Serial.print(mpr121_sensor.filteredData(i)); Serial.print("\t");
                        }
                        Serial.println();
                        Serial.print("Base: ");
                        for (uint8_t i=0; i<12; i++) {
                        Serial.print(mpr121_sensor.baselineData(i)); Serial.print("\t");
                        }

                        Serial.println();
                        Serial.println("\t --- End --- ");
                        Serial.println();
                } else {
                        mpr121_status = set_mpr121_initialization(
                                &mpr121_sensor, 0x5A);
                }

                vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
}


void mpu6050_task(void * pvParameters)
{
        Adafruit_MPU6050 mpu6050_sensor;
        boolean mpu6050_status = false;

        mpu6050_status = set_mpu6050_initialization(&mpu6050_sensor, 0x68);
        set_mpu6050_calibration(&mpu6050_sensor);

        while (1) {
                if (mpu6050_status) {
                        /* Get new sensor events with the readings */
                        sensors_event_t a, g, temp;
                        mpu6050_sensor.getEvent(&a, &g, &temp);

                        /* Print out the values */
                        Serial.print("Acceleration X: ");
                        Serial.print(a.acceleration.x);
                        Serial.print(", Y: ");
                        Serial.print(a.acceleration.y);
                        Serial.print(", Z: ");
                        Serial.print(a.acceleration.z);
                        Serial.println(" m/s^2");

                        Serial.print("Rotation X: ");
                        Serial.print(g.gyro.x);
                        Serial.print(", Y: ");
                        Serial.print(g.gyro.y);
                        Serial.print(", Z: ");
                        Serial.print(g.gyro.z);
                        Serial.println(" rad/s");

                        Serial.print("Temperature: ");
                        Serial.print(temp.temperature);
                        Serial.println(" degC");

                        Serial.println("");
                } else {
                        mpu6050_status = set_mpu6050_initialization(
                                &mpu6050_sensor, 0x68);
                }

                vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
}

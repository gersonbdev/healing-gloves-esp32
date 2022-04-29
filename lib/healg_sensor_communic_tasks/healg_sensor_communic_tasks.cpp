#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "healg_sensor_functions.hpp"
#include "healg_communic_functions.hpp"
#include "healg_sensor_communic_tasks.hpp"

Adafruit_MPR121 mpr121_sensor;
struct Mpr121Data mpr121_data;
boolean mpr121_status = false;

void mpr121_communic_task()
{
        if (!mpr121_status) {
                mpr121_status = set_mpr121_initialization(
                        &mpr121_sensor,
                        0x5A
                );
        }

        switch (HEALG_DEVICE_TYPE) {
        case CHIEF_TYPE_DEVICE:
                if (mpr121_status) {
                        save_data_from_mpr121(&mpr121_sensor, &mpr121_data);

                        send_data_from_mpr121_by_bluetooth(
                                &mpr121_data,
                                HEALG_DEVICE_TYPE
                        );
                }
                break;        
        default:
                break;
        }
}

Adafruit_MPU6050 mpu6050_sensor;
boolean mpu6050_status = false;

void mpu6050_communic_task()
{
        if (!mpu6050_status) {
                mpu6050_status = set_mpu6050_initialization(
                        &mpu6050_sensor,
                        0x68
                );

                if (mpu6050_status) {
                        set_mpu6050_calibration(&mpu6050_sensor);
                }
        }

        switch (HEALG_DEVICE_TYPE) {
        case CHIEF_TYPE_DEVICE:
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
                }
                break;        
        default:
                break;
        }
}
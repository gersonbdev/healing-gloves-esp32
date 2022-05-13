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

struct CapacitiveData capacitive_data;

void capacitive_communic_task()
{
        capacitive_data.pin[0] = touchRead(ESP32_TOUCH_PIN_9);
        capacitive_data.pin[1] = touchRead(ESP32_TOUCH_PIN_8);
        capacitive_data.pin[2] = touchRead(ESP32_TOUCH_PIN_7);
        capacitive_data.pin[3] = touchRead(ESP32_TOUCH_PIN_6);

        switch (HEALG_DEVICE_TYPE) {
        case CHIEF_TYPE_DEVICE:

                send_data_from_capacitive_by_bluetooth(
                        &capacitive_data,
                        HEALG_DEVICE_TYPE
                );
                
                break;        
        default:
                break;
        }


}


Adafruit_MPU6050 mpu6050_sensor;
struct Mpu6050Data mpu6050_data;
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
                        sensors_event_t a, g, temp;
                        mpu6050_sensor.getEvent(&a, &g, &temp);

                        mpu6050_data.acceleration_x = a.acceleration.x;
                        mpu6050_data.acceleration_y = a.acceleration.y;
                        mpu6050_data.acceleration_z = a.acceleration.z;

                        mpu6050_data.rotation_x = g.gyro.x;
                        mpu6050_data.rotation_y = g.gyro.y;
                        mpu6050_data.rotation_z = g.gyro.z;

                        mpu6050_data.temperature = temp.temperature;

                        send_data_from_mpu6050_by_bluetooth(
                                &mpu6050_data,
                                HEALG_DEVICE_TYPE
                        );
                }
                break;        
        default:
                break;
        }
}

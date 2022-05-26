#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "sensor_utilities.hpp"
#include "communic_utilities.hpp"
#include "healg_tasks.hpp"

struct ShippingDataSummary shipping_data_summary;

Adafruit_MPR121 mpr121_sensor;
struct Mpr121Data mpr121_data;
boolean mpr121_status = false;

struct CapacitiveData capacitive_data;

void keystrokes_task()
{
        String message = "";
        
        if (!mpr121_status) {
                mpr121_status = set_mpr121_initialization(
                        &mpr121_sensor,
                        0x5A
                );
        } else {
                save_data_from_mpr121(&mpr121_sensor, &mpr121_data);

                for (uint8_t i=0; i<12; i++) {
                        message += String(mpr121_data.pin[i]);
                        message += String(" ");
                        
                        if (mpr121_data.pin[i]<200) {
                                (shipping_data_summary.keystrokes)++;
                        }
                }
                Serial.println(message);
        }

        // save_data_from_capacitive(&capacitive_data);
        // for (uint8_t i=0; i<4; i++) {
        //         if (capacitive_data.pin[i]==0) {
        //                 (shipping_data_summary.keystrokes)++;
        //         }
        // }
}

Adafruit_MPU6050 mpu6050_sensor;
struct Mpu6050Data mpu6050_data, mpu6050_previous_data, mpu6050_exchange_data;
boolean mpu6050_status = false;

void rotations_task()
{
        if (!mpu6050_status) {
                mpu6050_status = set_mpu6050_initialization(
                        &mpu6050_sensor,
                        0x68
                );

                if (mpu6050_status) {
                        set_mpu6050_calibration(&mpu6050_sensor);
                        wipe_mpu6050_data(&mpu6050_previous_data);
                }
        } else {
                save_data_from_mpu6050(&mpu6050_sensor, &mpu6050_data);

                differentiate_mpu6050_data(
                        &mpu6050_data,
                        &mpu6050_previous_data,
                        &mpu6050_exchange_data
                );

                if (find_rotation_change_mpu6050(&mpu6050_exchange_data)) {
                        (shipping_data_summary.rotations)++;
                }
                
                mpu6050_previous_data = mpu6050_data;
        }
}

void communication_task()
{
        keystrokes_task();
        rotations_task();

        send_summary_data_via_bluetooth(&shipping_data_summary);
}

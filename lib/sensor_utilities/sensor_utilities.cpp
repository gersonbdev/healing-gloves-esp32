#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "sensor_utilities.hpp"


uint8_t set_mpr121_initialization(Adafruit_MPR121 *module, uint8_t i2c_address)
{
        if ((*module).begin(i2c_address)) {
                Serial.println("MPR121 found!");
                Serial.println("");
                
                return 1;
        } else {
                Serial.println("MPR121 not found, check wiring?");
                Serial.println("");

                return 0;
        }        
}


void save_data_from_mpr121(Adafruit_MPR121 *module, struct Mpr121Data *module_data)
{        
        for (uint8_t i=0; i<12; i++) {
                (*module_data).pin[i] = (*module).filteredData(i);
        }
}

void save_data_from_capacitive(struct CapacitiveData *module_data)
{
        (*module_data).pin[0] = touchRead(ESP32_TOUCH_PIN_6);
        (*module_data).pin[1] = touchRead(ESP32_TOUCH_PIN_7);
        (*module_data).pin[2] = touchRead(ESP32_TOUCH_PIN_8);
        (*module_data).pin[3] = touchRead(ESP32_TOUCH_PIN_9);
}


uint8_t set_mpu6050_initialization(Adafruit_MPU6050 *module, uint8_t i2c_address)
{
        if ((*module).begin(i2c_address)) {
                Serial.println("MPU6050 found!");
                Serial.println("");
                
                return 1;
        } else {
                Serial.println("MPU6050 not found, check wiring?");
                Serial.println("");

                return 0;
        }        
}

void set_mpu6050_calibration(Adafruit_MPU6050 *module)
{
        (*module).setAccelerometerRange(MPU6050_RANGE_8_G);
        Serial.print("Accelerometer range set to: ");

        switch ((*module).getAccelerometerRange()) {
        case MPU6050_RANGE_2_G:
                Serial.println("+-2G");
                break;
        case MPU6050_RANGE_4_G:
                Serial.println("+-4G");
                break;
        case MPU6050_RANGE_8_G:
                Serial.println("+-8G");
                break;
        case MPU6050_RANGE_16_G:
                Serial.println("+-16G");
                break;
        }

        (*module).setGyroRange(MPU6050_RANGE_500_DEG);
        Serial.print("Gyro range set to: ");

        switch ((*module).getGyroRange()) {
        case MPU6050_RANGE_250_DEG:
                Serial.println("+- 250 deg/s");
                break;
        case MPU6050_RANGE_500_DEG:
                Serial.println("+- 500 deg/s");
                break;
        case MPU6050_RANGE_1000_DEG:
                Serial.println("+- 1000 deg/s");
                break;
        case MPU6050_RANGE_2000_DEG:
                Serial.println("+- 2000 deg/s");
                break;
        }

        (*module).setFilterBandwidth(MPU6050_BAND_21_HZ);
        Serial.print("Filter bandwidth set to: ");
        
        switch ((*module).getFilterBandwidth()) {
        case MPU6050_BAND_260_HZ:
                Serial.println("260 Hz");
                break;
        case MPU6050_BAND_184_HZ:
                Serial.println("184 Hz");
                break;
        case MPU6050_BAND_94_HZ:
                Serial.println("94 Hz");
                break;
        case MPU6050_BAND_44_HZ:
                Serial.println("44 Hz");
                break;
        case MPU6050_BAND_21_HZ:
                Serial.println("21 Hz");
                break;
        case MPU6050_BAND_10_HZ:
                Serial.println("10 Hz");
                break;
        case MPU6050_BAND_5_HZ:
                Serial.println("5 Hz");
                break;
        }

        Serial.println("");
}

void save_data_from_mpu6050(
        Adafruit_MPU6050 *module,
        struct Mpu6050Data *module_data
)
{        
        sensors_event_t a, g, temp;
        (*module).getEvent(&a, &g, &temp);

        (*module_data).acceleration_x = a.acceleration.x;
        (*module_data).acceleration_y = a.acceleration.y;
        (*module_data).acceleration_z = a.acceleration.z;

        (*module_data).rotation_x = g.gyro.x;
        (*module_data).rotation_y = g.gyro.y;
        (*module_data).rotation_z = g.gyro.z;

        (*module_data).temperature = temp.temperature;
}

void wipe_mpu6050_data(struct Mpu6050Data *module_data)
{
        (*module_data).acceleration_x = 0;
        (*module_data).acceleration_y = 0;
        (*module_data).acceleration_z = 0;

        (*module_data).rotation_x = 0;
        (*module_data).rotation_y = 0;
        (*module_data).rotation_z = 0;

        (*module_data).temperature = 0;
}

void differentiate_mpu6050_data(
        struct Mpu6050Data *minuend,
        struct Mpu6050Data *subtrahend,
        struct Mpu6050Data *difference
)
{
        (*difference).acceleration_x = 
                (*minuend).acceleration_x - (*subtrahend).acceleration_x;
        (*difference).acceleration_y =
                (*minuend).acceleration_y - (*subtrahend).acceleration_y;
        (*difference).acceleration_z =
                (*minuend).acceleration_z - (*subtrahend).acceleration_z;

        (*difference).rotation_x =
                (*minuend).rotation_x - (*subtrahend).rotation_x;
        (*difference).rotation_y =
                (*minuend).rotation_y - (*subtrahend).rotation_y;
        (*difference).rotation_z =
                (*minuend).rotation_z - (*subtrahend).rotation_z;

        (*difference).temperature =
                (*minuend).temperature - (*subtrahend).temperature;
}

boolean find_rotation_change_mpu6050(struct Mpu6050Data *module_data)
{
        if ((*module_data).rotation_x > 1) {
                return true;
        }

        if ((*module_data).rotation_y > 1) {
                return true;
        }

        if ((*module_data).rotation_z > 1) {
                return true;
        }

        return false;
}
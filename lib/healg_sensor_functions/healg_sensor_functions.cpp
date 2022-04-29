#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "healg_sensor_functions.hpp"


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

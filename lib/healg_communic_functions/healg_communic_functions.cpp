#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "healg_sensor_functions.hpp"
#include "healg_communic_functions.hpp"

extern BluetoothSerial SerialBT;

void send_string_via_bluetooth(String *message)
{
        uint8_t buffer[(*message).length()];
        memcpy(buffer, (*message).c_str(), (*message).length());
        SerialBT.write(buffer, (*message).length());
}


void send_data_from_mpr121_by_bluetooth(struct Mpr121Data *module_data, uint8_t device_type)
{
        String message;
        
        message = String("data ") + String(device_type) + String(" ") +
                String(DATA_MESSAGE_TYPE_MPR121);

        for (uint8_t i=0; i<12; i++) {
                message += String(" ") + String((*module_data).pin[i]);
        }

        message += String(" \n\n\n");

        send_string_via_bluetooth(&message);
}

void send_data_from_capacitive_by_bluetooth(
        struct CapacitiveData *module_data,
        uint8_t device_type
)
{
        String message;
        
        message = String("data ") + String(device_type) + String(" ") +
                String(DATA_MESSAGE_TYPE_CAPACITIVE);

        for (uint8_t i=0; i<4; i++) {
                message += String(" ") + String((*module_data).pin[i]);
        }

        message += String(" \n\n\n");

        send_string_via_bluetooth(&message);
}

void send_data_from_mpu6050_by_bluetooth(
        struct Mpu6050Data *module_data,
        uint8_t device_type
)
{
        String message;
        
        message = String("data ") + String(device_type) + String(" ") +
                String(DATA_MESSAGE_TYPE_MPU6050);

        message += String(" ") + String((*module_data).acceleration_x);
        message += String(" ") + String((*module_data).acceleration_y);
        message += String(" ") + String((*module_data).acceleration_z);
        
        message += String(" ") + String((*module_data).rotation_x);
        message += String(" ") + String((*module_data).rotation_y);
        message += String(" ") + String((*module_data).rotation_z);
        
        message += String(" ") + String((*module_data).temperature);

        message += String(" \n\n\n");

        send_string_via_bluetooth(&message);      
}
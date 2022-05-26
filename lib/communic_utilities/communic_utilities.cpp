#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>

#include "healg_definitions.hpp"
#include "sensor_utilities.hpp"
#include "communic_utilities.hpp"

extern BluetoothSerial SerialBT;

void send_string_via_bluetooth(String message)
{
        uint8_t buffer[message.length()];
        memcpy(buffer, message.c_str(), message.length());
        SerialBT.write(buffer, message.length());
}

void send_summary_data_via_bluetooth(struct ShippingDataSummary *message_data)
{
        String message;

        message = String("key=");
        message += String((*message_data).keystrokes);
        message += String("\xff\xff\xff");
        send_string_via_bluetooth(message);  

        message = String("rot=");
        message += String((*message_data).rotations);
        message += String("\xff\xff\xff");
        send_string_via_bluetooth(message);  
}
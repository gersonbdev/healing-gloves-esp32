#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPR121.h>
#include <Adafruit_MPU6050.h>
#include <BluetoothSerial.h>

#include "healg_definitions.hpp"
#include "healg_communication_functions.hpp"

extern BluetoothSerial SerialBT;

void send_string_via_bluetooth(String *message)
{
        uint8_t buffer[(*message).length()];
        memcpy(buffer, (*message).c_str(), (*message).length());
        SerialBT.write(buffer, (*message).length());
}


void send_data_from_mpr121_by_bluetooth(Adafruit_MPR121 *module)
{
        uint16_t sensor_data;
        uint16_t previous_sensor_data;
        
        String message;
        
        sensor_data = (*module).touched();

        message = ("data " + String(HEALG_DEVICE_TYPE) + " " +
                String(DATA_MESSAGE_TYPE_MPR121) + " " + sensor_data + "\n"
        );

        send_string_via_bluetooth(&message);

        Serial.println(sensor_data);

        for (uint8_t i=0; i<12; i++) {
        // it if *is* touched and *wasnt* touched before, alert!
        if ((sensor_data & _BV(i)) && !(previous_sensor_data & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched");
        }
        // if it *was* touched and now *isnt*, alert!
        if (!(sensor_data & _BV(i)) && (previous_sensor_data & _BV(i)) ) {
        Serial.print(i); Serial.println(" released");
        }
        }

        // reset our state
        previous_sensor_data = sensor_data;

        //delay(200);

        // comment out this line for detailed data from the sensor!
        //return;

        // debugging info, what
        Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println((*module).touched(), HEX);
        Serial.print("Filt: ");
        for (uint8_t i=0; i<12; i++) {
        Serial.print((*module).filteredData(i)); Serial.print("\t");
        }
        Serial.println();
        Serial.print("Base: ");
        for (uint8_t i=0; i<12; i++) {
        Serial.print((*module).baselineData(i)); Serial.print("\t");
        }

        Serial.println();
        Serial.println("\t --- End --- ");
        Serial.println();
}

// SerialBT.write
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPR121.h>

#include "healg_definitions.hpp"
#include "healg_sensor_tasks.hpp"


Adafruit_MPR121 device_mpr121 = Adafruit_MPR121();
boolean mpr121_status = false;

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void mpr121_task(void * pvParameters)
{
        
        // Default address is 0x5A, if tied to 3.3V its 0x5B
        // If tied to SDA its 0x5C and if SCL then 0x5D
        if (device_mpr121.begin(0x5A)) {
                mpr121_status = true;
                Serial.println("MPR121 found!");
        } else {
                mpr121_status = false;
                Serial.println("MPR121 not found, check wiring?");
        }

        while (1) {                
                if (mpr121_status) {
                        Serial.println();
                        Serial.println("\t --- Begin --- ");
                        Serial.println();
                        // Get the currently touched pads
                        currtouched = device_mpr121.touched();

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
                        Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(device_mpr121.touched(), HEX);
                        Serial.print("Filt: ");
                        for (uint8_t i=0; i<12; i++) {
                        Serial.print(device_mpr121.filteredData(i)); Serial.print("\t");
                        }
                        Serial.println();
                        Serial.print("Base: ");
                        for (uint8_t i=0; i<12; i++) {
                        Serial.print(device_mpr121.baselineData(i)); Serial.print("\t");
                        }

                        Serial.println();
                        Serial.println("\t --- End --- ");
                        Serial.println();

                        vTaskDelay(1000 / portTICK_PERIOD_MS);
                } else {
                        if (device_mpr121.begin(0x5A)) {
                                mpr121_status = true;
                                Serial.println("MPR121 found!");
                        } else {
                                mpr121_status = false;
                                Serial.println("MPR121 not found, check wiring?");
                        }
                        
                        vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
        }
}
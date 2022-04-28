#ifndef healg_communication_functions_hpp

#define healg_communication_functions_hpp

#define DATA_MESSAGE_TYPE_MPR121 1

void send_string_via_bluetooth(String *message);

void send_data_from_mpr121_by_bluetooth(Adafruit_MPR121 *module);

#endif
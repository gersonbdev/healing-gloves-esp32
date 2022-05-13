#ifndef healg_communic_functions_hpp

#define healg_communic_functions_hpp

#define DATA_MESSAGE_TYPE_MPR121 1
#define DATA_MESSAGE_TYPE_CAPACITIVE 2
#define DATA_MESSAGE_TYPE_MPU6050 3

void send_string_via_bluetooth(String *message);

void send_data_from_mpr121_by_bluetooth(
        struct Mpr121Data *module_data,
        uint8_t device_type
);

void send_data_from_capacitive_by_bluetooth(
        struct CapacitiveData *module_data,
        uint8_t device_type
);

void send_data_from_mpu6050_by_bluetooth(
        struct Mpu6050Data *module_data,
        uint8_t device_type
);

#endif
#ifndef healg_communic_functions_hpp

#define healg_communic_functions_hpp

#define DATA_MESSAGE_TYPE_MPR121     1
#define DATA_MESSAGE_TYPE_CAPACITIVE 2
#define DATA_MESSAGE_TYPE_MPU6050    3

struct DataForAppInventor {
        uint32_t sum_of_actions;
        uint32_t keystrokes;
        uint32_t rotations;
};

void send_string_via_bluetooth(String *message);

void send_data_from_mpr121_by_bluetooth(
        uint8_t device_type,
        struct Mpr121Data *module_data
);

void send_data_from_capacitive_by_bluetooth(
        uint8_t device_type,
        struct CapacitiveData *module_data
);

void send_data_from_mpu6050_by_bluetooth(
        uint8_t device_type,
        struct Mpu6050Data *module_data
);

void send_data_to_app_inventor(struct DataForAppInventor *message_data);

#endif
#ifndef healg_sensor_functions_hpp

#define healg_sensor_functions_hpp

struct Mpr121Data {
        uint16_t pin[12];
};

struct CapacitiveData {
        uint16_t pin[4];
};

struct Mpu6050Data {
        float acceleration_x;
        float acceleration_y;
        float acceleration_z;

        float rotation_x;
        float rotation_y;
        float rotation_z;

        float temperature;
};

uint8_t set_mpr121_initialization(Adafruit_MPR121 *module, uint8_t i2c_address);
void save_data_from_mpr121(Adafruit_MPR121 *module, struct Mpr121Data *module_data);

void save_data_from_capacitive(struct CapacitiveData *module_data);

uint8_t set_mpu6050_initialization(Adafruit_MPU6050 *module, uint8_t i2c_address);
void set_mpu6050_calibration(Adafruit_MPU6050 *module);

void save_data_from_mpu6050(
        Adafruit_MPU6050 *module,
        struct Mpu6050Data *module_data
);

void wipe_mpu6050_data(struct Mpu6050Data *module_data);

void differentiate_mpu6050_data(
        struct Mpu6050Data *minuend,
        struct Mpu6050Data *subtrahend,
        struct Mpu6050Data *difference
);

boolean find_rotation_change_mpu6050(
        struct Mpu6050Data *module_data
);

#endif

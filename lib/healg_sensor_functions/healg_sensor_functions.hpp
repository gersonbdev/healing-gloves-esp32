#ifndef healg_sensor_functions_hpp

#define healg_sensor_functions_hpp



uint8_t set_mpr121_initialization(Adafruit_MPR121 *module, uint8_t i2c_address);
uint8_t set_mpu6050_initialization(Adafruit_MPU6050 *module, uint8_t i2c_address);
void set_mpu6050_calibration(Adafruit_MPU6050 *module);

#endif

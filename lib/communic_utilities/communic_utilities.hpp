#ifndef communic_utilities_hpp

#define communic_utilities_hpp

#define DATA_MESSAGE_TYPE_MPR121     1
#define DATA_MESSAGE_TYPE_CAPACITIVE 2
#define DATA_MESSAGE_TYPE_MPU6050    3

struct ShippingDataSummary {
        uint32_t sum_of_actions = 0;
        uint32_t keystrokes = 0;
        uint32_t rotations = 0;
};

void send_string_via_bluetooth(String message);

void send_summary_data_via_bluetooth(struct ShippingDataSummary *message_data);

#endif
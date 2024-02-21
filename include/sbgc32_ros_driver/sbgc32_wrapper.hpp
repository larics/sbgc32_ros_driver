#ifndef SBGC32_WRAPPER
#define SBGC32_WRAPPER
extern "C" void init_gimbal();
extern "C" void set_gimbal_pitch_yaw(double pitch_deg, double yaw_deg);
extern "C" void get_real_time_data();

extern "C" int get_acc_roll();
extern "C" int get_acc_pitch();
extern "C" int get_acc_yaw();
extern "C" int get_gyro_roll();
extern "C" int get_gyro_pitch();
extern "C" int get_gyro_yaw();
#endif


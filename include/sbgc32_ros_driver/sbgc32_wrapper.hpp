#ifndef SBGC32_WRAPPER
#define SBGC32_WRAPPER
extern "C" void init_gimbal();
extern "C" void set_gimbal_pitch_yaw(double pitch_deg, double yaw_deg);
#endif


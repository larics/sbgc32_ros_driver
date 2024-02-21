#include <ros/ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <sbgc32_ros_driver/sbgc32_wrapper.hpp>
#include <sensor_msgs/Imu.h>

void callback(const geometry_msgs::Vector3Stamped& msg) {
  set_gimbal_pitch_yaw(msg.vector.y * 180 / M_PI, msg.vector.z * 180 / M_PI);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "sbgc32_node");
  int rate = 1000;
  init_gimbal();
  ros::NodeHandle nh;
  auto            sub = nh.subscribe("sbgc32/target", 1, &callback);
  auto imu_pub = nh.advertise<sensor_msgs::Imu>("sbgc32/imu", 1);
  ros::Rate loop_rate(rate);
  sensor_msgs::Imu imu_msg;
  while (ros::ok())
  {
      ros::spinOnce();
      get_real_time_data();
      imu_msg.header.stamp = ros::Time::now();

      imu_msg.linear_acceleration.x = get_acc_roll();
      imu_msg.linear_acceleration.y = get_acc_pitch();
      imu_msg.linear_acceleration.z = get_acc_yaw();

      imu_msg.angular_velocity.x = get_gyro_roll();
      imu_msg.angular_velocity.y = get_gyro_pitch();
      imu_msg.angular_velocity.z = get_gyro_yaw();

      loop_rate.sleep();
  }
  return 0;
}

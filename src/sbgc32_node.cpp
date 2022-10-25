#include <ros/ros.h>
#include <sbgc32_ros_driver/sbgc32_wrapper.hpp>
#include <geometry_msgs/Vector3Stamped.h>

SBGC32Wrapper wrapper;

void callback(const geometry_msgs::Vector3Stamped& msg) {
  wrapper.SetPitchYaw(msg.vector.y * 180 / M_PI, msg.vector.z * 180 / M_PI);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "sbgc32_node");
  ros::NodeHandle nh;
  auto            sub = nh.subscribe("sbgc32/target", 1, &callback);
  ros::spin();
  return 0;
}

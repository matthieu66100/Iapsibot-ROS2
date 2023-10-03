#ifndef WEBOTS_ROS2_PLUGIN_EXAMPLE_HPP
#define WEBOTS_ROS2_PLUGIN_EXAMPLE_HPP

#include "rclcpp/macros.hpp"
#include "webots_ros2_driver/PluginInterface.hpp"
#include "webots_ros2_driver/WebotsNode.hpp"

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"

namespace robot_sim {
  class RobotDriver : public webots_ros2_driver::PluginInterface {
  public:
    void step() override;
    void init(webots_ros2_driver::WebotsNode *node,
              std::unordered_map<std::string, std::string> &parameters) override;

  private:
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr mCmdVelSubscription;
    geometry_msgs::msg::Twist mCmdVelMsg;

    WbDeviceTag mRightMotor;
    WbDeviceTag mLeftMotor;

    const double mHALF_DISTANCE_BETWEEN_WHEELS = 0.045;
    const double mWHEEL_RADIUS =  0.025;
  };
} // namespace robot_sim
#endif
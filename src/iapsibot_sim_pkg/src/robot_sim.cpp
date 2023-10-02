// #include "robot_sim.hpp"
#include "robot_sim.hpp"

#include "rclcpp/rclcpp.hpp"
#include <cstdio>
#include <functional>
#include <webots/motor.h>
#include <webots/robot.h>

#include "pluginlib/class_list_macros.hpp"

#define HALF_DISTANCE_BETWEEN_WHEELS 0.045
#define WHEEL_RADIUS 0.025

namespace robot_sim {

  void RobotDriver::init(
      webots_ros2_driver::WebotsNode *node,
      std::unordered_map<std::string, std::string> &parameters) {

    right_motor = wb_robot_get_device("right wheel motor");
    left_motor = wb_robot_get_device("left wheel motor");

    wb_motor_set_position(left_motor, INFINITY);
    wb_motor_set_velocity(left_motor, 0.0);

    wb_motor_set_position(right_motor, INFINITY);
    wb_motor_set_velocity(right_motor, 0.0);

    cmd_vel_subscription_ = node->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", rclcpp::SensorDataQoS().reliable(),
        std::bind(&RobotDriver::cmdVelCallback, this, std::placeholders::_1));
  }

  void RobotDriver::cmdVelCallback(
      const geometry_msgs::msg::Twist::SharedPtr msg) {
    cmd_vel_msg.linear = msg->linear;
    cmd_vel_msg.angular = msg->angular;
  }

  void RobotDriver::step() {
    auto forward_speed = cmd_vel_msg.linear.x;
    auto angular_speed = cmd_vel_msg.angular.z;

    auto command_motor_left =
        (forward_speed - angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) /
        WHEEL_RADIUS;
    auto command_motor_right =
        (forward_speed + angular_speed * HALF_DISTANCE_BETWEEN_WHEELS) /
        WHEEL_RADIUS;

    wb_motor_set_velocity(left_motor, command_motor_left);
    wb_motor_set_velocity(right_motor, command_motor_right);
  }
  
} // namespace robot_sim


PLUGINLIB_EXPORT_CLASS(robot_sim::RobotDriver,
                       webots_ros2_driver::PluginInterface)
// #include "robot_sim.hpp"
#include "robot_sim.hpp"

#include "rclcpp/rclcpp.hpp"
#include <cstdio>
#include <functional>
#include <webots/motor.h>
#include <webots/robot.h> 

#include "pluginlib/class_list_macros.hpp"

namespace robot_sim {

  void RobotDriver::init(
    webots_ros2_driver::WebotsNode *node,
    std::unordered_map<std::string, std::string> &parameters) {

    mRightMotor = wb_robot_get_device("right wheel motor");
    mLeftMotor = wb_robot_get_device("left wheel motor");

    wb_motor_set_position(mLeftMotor, INFINITY);
    wb_motor_set_velocity(mLeftMotor, 0.0);

    wb_motor_set_position(mRightMotor, INFINITY);
    wb_motor_set_velocity(mRightMotor, 0.0);

    mCmdVelSubscription = node->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", rclcpp::SensorDataQoS().reliable(),
        std::bind(&RobotDriver::cmdVelCallback, this, std::placeholders::_1));
  }

  void RobotDriver::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    mCmdVelMsg.linear = msg->linear;
    mCmdVelMsg.angular = msg->angular;
  }

  void RobotDriver::step() {
    auto forward_speed = mCmdVelMsg.linear.x;
    auto angular_speed = mCmdVelMsg.angular.z;

    auto command_motor_left =
        (forward_speed - angular_speed * mHALF_DISTANCE_BETWEEN_WHEELS) /
        mWHEEL_RADIUS;
    auto command_motor_right =
        (forward_speed + angular_speed * mHALF_DISTANCE_BETWEEN_WHEELS) /
        mWHEEL_RADIUS;

    wb_motor_set_velocity(mLeftMotor, command_motor_left);
    wb_motor_set_velocity(mRightMotor, command_motor_right);
  }
  
} // namespace robot_sim


PLUGINLIB_EXPORT_CLASS(robot_sim::RobotDriver,
                       webots_ros2_driver::PluginInterface)
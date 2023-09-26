#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <memory>
#include <functional>
#include <array>

// Message types
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "iapsibot_interfaces_pkg/msg/wheels.hpp"
#include "iapsibot_interfaces_pkg/msg/sonar_ranges.hpp"

using namespace std::chrono_literals;

/**
 * @brief TestComPublisher : Teste la réception d'image, l'etat du robot et publie les commandes vers le robot
 */
class TestComPublisher : public rclcpp::Node
{
public:
  TestComPublisher() 
  : Node("test_com_publisher"), mCount(0)
  {
    constexpr size_t queuesSize{10};

    mStringPublisher = this->create_publisher<std_msgs::msg::String>("stringTopic", queuesSize);
    mWheelPublisher = this->create_publisher<iapsibot_interfaces_pkg::msg::Wheels>("wheelTopic", queuesSize);
    mSonarRangesPublisher = this->create_publisher<iapsibot_interfaces_pkg::msg::SonarRanges>("sonarTopic", queuesSize);

    mTimer = this->create_wall_timer(
      1000ms, 
      std::bind(&TestComPublisher::timerCallbackString, this)
    );
    
  }

private:
  size_t mCount;

  void timerCallbackString()
  {
    switch(mCount++%3){
      case 0:
        publishString();
        break;

      case 1:
        publishWheels();
        break;

      case 2:
        publishSonar();
        break;
    }
  }

  //Timer pour les envois periodiques
  rclcpp::TimerBase::SharedPtr mTimer;

  //Publoshers de tests des différents types
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mStringPublisher;
  rclcpp::Publisher<iapsibot_interfaces_pkg::msg::Wheels>::SharedPtr mWheelPublisher;
  rclcpp::Publisher<iapsibot_interfaces_pkg::msg::SonarRanges>::SharedPtr mSonarRangesPublisher;

  void publishString(){
    std_msgs::msg::String message;
    message.data = "Bonjour le monde " + std::to_string(mCount);

    RCLCPP_INFO(this->get_logger(), "Publishing a 🗣️ string 🗣️ : '%s'\n", message.data.c_str());
    mStringPublisher->publish(message);
  }

  void publishWheels(){
    iapsibot_interfaces_pkg::msg::Wheels msg;
    msg.left_wheel_rotation_rad = static_cast<float>(mCount);

    RCLCPP_INFO(get_logger(), "Publishing a 🛞 wheel 🛞 msg with left_wheel_rotation_rad '%f'\n", msg.left_wheel_rotation_rad);
    mWheelPublisher->publish(msg);
  }

  void publishSonar(){
    iapsibot_interfaces_pkg::msg::SonarRanges msg;
    msg.range_center_sonar.range = static_cast<float>(mCount);

    RCLCPP_INFO(get_logger(), "Publishing a 🔊 sonar 🔊 msg with range_center_sonar.range : '%f'\n", msg.range_center_sonar.range);
    mSonarRangesPublisher->publish(msg);
  }


};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  iapsibot_interfaces_pkg::msg::SonarRanges sonarRangesTestCreation;

  rclcpp::spin(std::make_shared<TestComPublisher>());
  rclcpp::shutdown();
  return 0;
}

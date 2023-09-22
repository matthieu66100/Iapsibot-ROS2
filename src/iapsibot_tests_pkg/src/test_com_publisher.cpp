#include <chrono>
#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"

using namespace std::chrono_literals;

/**
 * @brief Teste la réception d'image, l'etat du robot et publie les commandes vers le robot
 */
class TestComPublisher : public rclcpp::Node
{
public:
  TestComPublisher()
  : Node("test_com_publisher"), mCount(0)
  {
    mPublisher = this->create_publisher<std_msgs::msg::String>("stringTopic", 10);
    mTimer = this->create_wall_timer(
      500ms, std::bind(&TestComPublisher::timerCallbackString, this));
    
  }

private:
  void timerCallbackString()
  {
    auto message = std_msgs::msg::String();
    message.data = "🤖 : Bonjour le monde " + std::to_string(mCount++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    mPublisher->publish(message);
  }
  rclcpp::TimerBase::SharedPtr mTimer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr mPublisher;
  size_t mCount;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestComPublisher>());
  rclcpp::shutdown();
  return 0;
}

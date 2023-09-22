#include "rclcpp/rclcpp.hpp"

#include <memory>
#include <functional>
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"


using std::placeholders::_1;

class TestComSuscriber : public rclcpp::Node
{
public:
    TestComSuscriber(): Node("test_com_suscriber")
    {
        //String topic

        mSuscription = this->create_subscription<std_msgs::msg::String>("stringTopic", 10, 
            std::bind(&TestComSuscriber::callbackFunctionString, this, _1)
        );
    }
private:

    void callbackFunctionString(std::shared_ptr<const std_msgs::msg::String> msg){

        std::stringstream printedMsg;
        printedMsg << "[I heard on topic 'stringTopic'] : " << msg->data; 
        RCLCPP_INFO(this->get_logger(), printedMsg.str().c_str());
    }

    std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> mSuscription; 
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestComSuscriber>());
  rclcpp::shutdown();

  return 0;
}
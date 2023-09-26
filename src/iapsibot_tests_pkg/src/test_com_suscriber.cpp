#include "rclcpp/rclcpp.hpp"
#include <memory>
#include <functional>

#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "iapsibot_interfaces_pkg/msg/wheels.hpp"
#include "iapsibot_interfaces_pkg/msg/sonar_ranges.hpp"


using std::placeholders::_1;

class TestComSuscriber : public rclcpp::Node
{
public:
    TestComSuscriber(): Node("test_com_suscriber")
    {
        // String topic
        mStringSuscription = this->create_subscription<std_msgs::msg::String>("stringTopic", 10, 
            std::bind(&TestComSuscriber::callbackFunctionString, this, _1) //On utilise bind pour créer un callback via une methode
        );

        // Wheel topic
        mWheelSuscription = this->create_subscription<iapsibot_interfaces_pkg::msg::Wheels>("wheelTopic", 10, 
            //Définition du callback via lambda
            std::bind(&TestComSuscriber::callbackFunctionWheel, this, _1)
        );
        
        // Sonar topic
        mSonarSuscription = this->create_subscription<iapsibot_interfaces_pkg::msg::SonarRanges>("sonarTopic", 10, 
            std::bind(&TestComSuscriber::callbackFunctionSonar, this, _1)
        );

    }
private:

    void callbackFunctionString(std::shared_ptr<const std_msgs::msg::String> msg){
        std::stringstream printedMsg;
        printedMsg << "[I heard on topic 🗣️ 'stringTopic' 🗣️ ] : " << msg->data << '\n'; 
        RCLCPP_INFO(this->get_logger(), printedMsg.str().c_str());
    }

    void callbackFunctionWheel(iapsibot_interfaces_pkg::msg::Wheels::SharedPtr msg){
        std::stringstream printedMsg;
        printedMsg << "[I heard on topic 🛞 'wheelTopic' 🛞 ] : " << msg->left_wheel_rotation_rad << '\n';
        RCLCPP_INFO(this->get_logger(), printedMsg.str().c_str());
    }

    void callbackFunctionSonar(iapsibot_interfaces_pkg::msg::SonarRanges::SharedPtr msg){
        std::stringstream printedMsg;
        printedMsg << "[I heard on topic 🔊 'sonarTopic' 🔊 ] : " << msg->range_center_sonar.range << '\n';
        RCLCPP_INFO(this->get_logger(), printedMsg.str().c_str());
    }

    std::shared_ptr<rclcpp::Subscription<std_msgs::msg::String>> mStringSuscription; 
    std::shared_ptr<rclcpp::Subscription<iapsibot_interfaces_pkg::msg::Wheels>> mWheelSuscription; 
    std::shared_ptr<rclcpp::Subscription<iapsibot_interfaces_pkg::msg::SonarRanges>> mSonarSuscription; 
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TestComSuscriber>());
    rclcpp::shutdown();

    return 0;
}
cmake_minimum_required(VERSION 3.8)
project(iapsibot_tests_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
#Libs ROS2
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Lib OpenCV
find_package(OpenCV 4 REQUIRED)

# Custom interfaces
find_package(iapsibot_interfaces_pkg REQUIRED)

# test publisher
add_executable(test_com_publisher src/test_com_publisher.cpp)
target_include_directories(test_com_publisher PRIVATE ./ iapsibot_interfaces_pkg)
ament_target_dependencies(test_com_publisher rclcpp std_msgs sensor_msgs iapsibot_interfaces_pkg)

# test suscriber
add_executable(test_com_suscriber src/test_com_suscriber.cpp)
target_include_directories(test_com_suscriber PRIVATE ./)

ament_target_dependencies(test_com_suscriber rclcpp std_msgs sensor_msgs iapsibot_interfaces_pkg)

# Installs
install(TARGETS test_com_publisher DESTINATION lib/${PROJECT_NAME})
install(TARGETS test_com_suscriber DESTINATION lib/${PROJECT_NAME})

#Specification du type de pkg
ament_package()
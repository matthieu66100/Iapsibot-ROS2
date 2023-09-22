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

# test publisher
add_executable(test_com_publisher src/test_com_publisher.cpp)
target_include_directories(test_com_publisher PRIVATE ./)
target_include_directories(test_com_publisher PRIVATE ${rclcpp_INCLUDE_DIRS})
target_link_libraries(test_com_publisher ${rclcpp_LIBRARIES})
target_include_directories(test_com_publisher PRIVATE ${std_msgs_INCLUDE_DIRS})
target_link_libraries(test_com_publisher ${std_msgs_LIBRARIES})
target_include_directories(test_com_publisher PRIVATE ${sensor_msgs_INCLUDE_DIRS})
target_link_libraries(test_com_publisher ${sensor_msgs_LIBRARIES})
ament_target_dependencies(test_com_publisher rclcpp std_msgs)

# test suscriber
add_executable(test_com_suscriber src/test_com_suscriber.cpp)
target_include_directories(test_com_suscriber PRIVATE ./)
target_include_directories(test_com_suscriber PRIVATE ${rclcpp_INCLUDE_DIRS})
target_include_directories(test_com_suscriber PRIVATE ${std_msgs_INCLUDE_DIRS})
target_include_directories(test_com_suscriber PRIVATE ${sensor_msgs_INCLUDE_DIRS})
target_link_libraries(test_com_suscriber ${sensor_msgs_LIBRARIES})
ament_target_dependencies(test_com_suscriber rclcpp std_msgs)

# Installs
install(TARGETS test_com_publisher DESTINATION lib/${PROJECT_NAME})
install(TARGETS test_com_suscriber DESTINATION lib/${PROJECT_NAME})

#Specification du type de pkg
ament_package()
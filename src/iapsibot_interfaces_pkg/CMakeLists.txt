cmake_minimum_required(VERSION 3.8)
project(iapsibot_interfaces_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED) # For access to existing interfaces
find_package(sensor_msgs REQUIRED)

find_package(rosidl_default_generators REQUIRED) #For generating interfaces
rosidl_generate_interfaces(${PROJECT_NAME} 
  "msg/Wheels.msg"
  "msg/SonarRanges.msg"
  DEPENDENCIES sensor_msgs
)

ament_export_dependencies(rosidl_default_runtime sensor_msgs builtin_interfaces)

ament_package()

cmake_minimum_required(VERSION 3.8)
project(iapsibot_interfaces_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED) #For generatign interfaces
find_package(builtin_interfaces REQUIRED) # For access to existing interfaces
find_package(sensor_msgs REQUIRED)

rosidl_generate_interfaces(${PROJET_NAME} "msg/Wheels.msg")

ament_export_dependencies(rosidl_default_runtime)

ament_package()

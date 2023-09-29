cmake_minimum_required(VERSION 3.8)
project(iapsibot_sim_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(webots_ros2_driver REQUIRED) #Cant find this package
find_package(pluginlib REQUIRED)

add_executable(robot_sim src/robot_sim.cpp)

target_include_directories(robot_sim PUBLIC
  include/${PROJECT_NAME}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_features(robot_sim PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  robot_sim
  "rclcpp"
  "geometry_msgs"
  "webots_ros2_driver"
  "pluginlib"
)



install(TARGETS robot_sim
  DESTINATION lib/${PROJECT_NAME})


ament_package()

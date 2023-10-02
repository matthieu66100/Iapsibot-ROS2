# cmake_minimum_required(VERSION 3.8)
# project(iapsibot_sim_pkg)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# # find dependencies
# find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(geometry_msgs REQUIRED)
# find_package(webots_ros2_driver REQUIRED) #Cant find this package
# find_package(pluginlib REQUIRED)

# add_executable(robot_sim src/robot_sim.cpp)

# target_include_directories(robot_sim PUBLIC
#   include/${PROJECT_NAME}
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>
# )

# target_compile_features(robot_sim PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# ament_target_dependencies(
#   robot_sim
#   "rclcpp"
#   "geometry_msgs"
#   "webots_ros2_driver"
#   "pluginlib"
# )



# install(TARGETS robot_sim
#   DESTINATION lib/${PROJECT_NAME})


# ament_package()




cmake_minimum_required(VERSION 3.5)
project(iapsibot_sim_pkg)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Besides the package specific dependencies we also need the `pluginlib` and `webots_ros2_driver`
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(webots_ros2_driver REQUIRED)

# Export the plugin configuration file
pluginlib_export_plugin_description_file(webots_ros2_driver robot_sim.xml)

# MyRobotDriver library
add_library(
  ${PROJECT_NAME}
  SHARED
  src/robot_sim.cpp
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  include
  include/${PROJECT_NAME}
)

ament_target_dependencies(
  ${PROJECT_NAME}
  pluginlib
  rclcpp
  webots_ros2_driver
)

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install additional directories.
install(DIRECTORY
  launch
  resource
  worlds
  DESTINATION share/${PROJECT_NAME}/
)

ament_export_include_directories(
  include
)

ament_export_libraries(
  ${PROJECT_NAME}
)

ament_package()
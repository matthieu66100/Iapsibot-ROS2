FROM ros:humble-ros-base

# Update and install packages and tools
RUN apt-get update && apt-get install -y git wget python3-pip vim
RUN pip3 install setuptools==58.2.0

# Add dependencies and extra-packages without download
COPY ./dependencies /dependencies
WORKDIR /dependencies

# Install dependencies and extra-packages
RUN apt-get update && apt-get install -y ros-humble-turtlesim
RUN apt-get install -y ./webots_2023b_amd64.deb

# Add ros2 workspace and use it in work-directory
COPY ./src /ros2_ws/src
WORKDIR /ros2_ws

# Set the display on NOVNC docker
ENV DISPLAY=novnc:0.0

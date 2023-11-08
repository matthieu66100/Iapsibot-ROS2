FROM osrf/ros:humble-desktop

EXPOSE 1234

SHELL ["/bin/bash", "-c"]

# Update and install packages and tools
RUN apt-get update && apt-get install -y git wget python3-pip python3-rosdep python3-colcon-common-extensions vim
RUN pip3 install setuptools==58.2

# Installing webots
# Adding signature file
RUN sudo mkdir -p /etc/apt/keyrings &&cd /etc/apt/keyrings && sudo wget -q https://cyberbotics.com/Cyberbotics.asc
# Add Cyberbotics repository to apt sources
RUN echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/Cyberbotics.asc] https://cyberbotics.com/debian binary-amd64/" | sudo tee /etc/apt/sources.list.d/Cyberbotics.list && sudo apt update
# Install webots
# sudo apt install webots


# Copiez le script de configuration ROS 2 dans le conteneur
COPY ros_setup.bash /ros_setup.bash
# Donnez les autorisations d'exécution au script
RUN chmod +x /ros_setup.bash
# Ajoutez la commande source au fichier ~/.bashrc
RUN echo "source /ros_setup.bash" >> ~/.bashrc


RUN mkdir -p ~/ros2_ws/src && source /opt/ros/humble/setup.bash

RUN cd ~/ros2_ws && git clone --recurse-submodules https://github.com/cyberbotics/webots_ros2.git src/webots_ros2

RUN rm -rf /etc/ros/rosdep/sources.list.d/20-default.list

RUN rosdep init && rosdep update && rosdep install --from-paths ~/ros2_ws/src --ignore-src --rosdistro humble -y

RUN colcon build

RUN source ~/ros2_ws/install/local_setup.bash


# Add ros2 workspace and use it in work-directory
COPY ./src /ros2_ws/src
WORKDIR /ros2_ws

# Set the display on NOVNC docker
ENV DISPLAY=novnc:0.0
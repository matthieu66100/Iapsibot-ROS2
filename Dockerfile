FROM osrf/ros:humble-desktop

VOLUME [ "/usr/local/webots" ]

# Expose port 1234 for webots
EXPOSE 1234
# Use bash instead of sh
SHELL ["/bin/bash", "-c"]
# Copy the pkg list to the container
# COPY ./src /ros2_ws/src

# Remove old version of rosdep depencies
RUN rm -rf /etc/ros/rosdep/sources.list.d/20-default.list

# Update and install packages and tools
RUN apt-get update && apt-get install -y git wget python3-pip python3-rosdep python3-colcon-common-extensions vim
RUN pip3 install setuptools==58.2

# Copiez le script de configuration ROS 2 dans le conteneur
COPY ros_setup.bash /ros_setup.bash
# Donnez les autorisations d'exécution au script
RUN chmod +x /ros_setup.bash
# Ajoutez la commande source au fichier ~/.bashrc
RUN echo "source /ros_setup.bash" >> ~/.bashrc

# Remove old version of rosdep depencies
RUN rm -rf /etc/ros/rosdep/sources.list.d/20-default.list

# Source the setup file in humble
RUN source /opt/ros/humble/setup.bash
# run rosdep update to update the package dependencies
RUN rosdep init && rosdep update 

COPY ./src /ros2_ws/src
# Install dependencies
RUN cd /ros2_ws && rosdep install --from-paths src --ignore-src --rosdistro humble -y

# Set the display on NOVNC docker
ENV DISPLAY=novnc:0.0

# Set the webots home

ENV WEBOTS_HOME=/usr/local/webots

# Set the working directory to /ros2_ws
WORKDIR /ros2_ws
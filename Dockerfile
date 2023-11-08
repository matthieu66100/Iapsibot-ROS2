FROM ros:humble-ros-base

SHELL ["/bin/bash", "-c"]

# Update and install packages and tools
RUN apt-get update && apt-get install -y git wget python3-pip vim
RUN pip3 install setuptools==58.2

# Copiez le script de configuration ROS 2 dans le conteneur
COPY ros_setup.bash /ros_setup.bash

# Donnez les autorisations d'exécution au script
RUN chmod +x /ros_setup.bash

# Ajoutez la commande source au fichier ~/.bashrc
RUN echo "source /ros_setup.bash" >> ~/.bashrc


# Add ros2 workspace and use it in work-directory
COPY ./src /ros2_ws/src
WORKDIR /ros2_ws

# Set the display on NOVNC docker
ENV DISPLAY=novnc:0.0
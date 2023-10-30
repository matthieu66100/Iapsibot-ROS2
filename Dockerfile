FROM ros:humble-ros-base

RUN apt-get update && apt-get install -y git wget python3-pip vim
RUN pip3 install setuptools==58.2.0

COPY ./src/ /ros2_ws
WORKDIR /ros2_ws
RUN colcon build

ENV DISPLAY=novnc:0.0

FROM osrf/ros:humble-desktop-full

RUN sudo apt-get update && apt-get install -y git wget python3-pip vim
RUN pip3 install setuptools==58.2.0

RUN git clone https://github.com/divyanshuraj6815/experiments.git
RUN git config --global user.email "matthieu.basto@gmail.com"
RUN git config --global user.name "matthieu66100"

ENV DISPLAY=novnc:0.0

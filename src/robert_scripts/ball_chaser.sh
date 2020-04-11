#!/bin/bash

# Build the catkin_ws
cd $(pwd)/../..; catkin build

# Launch the nodes
xterm -geometry 50x15+500+250 -e "source devel/setup.bash; roslaunch robert  myoffice_world.launch" &
sleep 10

xterm -geometry 50x15+805+250 -e "source devel/setup.bash; roslaunch robert amcl.launch " &
sleep 5

xterm -geometry 50x15+805+488 -e "source devel/setup.bash; roslaunch robert_ball_chaser robert_ball_chaser.launch "



#!/bin/bash

# Build the catkin_ws
cd $(pwd)/../..; catkin build

# Launch the nodes
xterm -geometry 50x15+500+250  -e "source devel/setup.bash; roslaunch robert  myoffice_world.launch" &
sleep 10

xterm -geometry 50x15+805+250 -e "source devel/setup.bash; roslaunch robert amcl.launch " &
sleep 5

xterm -geometry 50x15+500+488  -e "source devel/setup.bash; roslaunch robert_rviz_launchers view_navigation.launch" &



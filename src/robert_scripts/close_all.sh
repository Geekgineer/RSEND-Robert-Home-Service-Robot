#!/bin/bash

rosnode kill -a ; killall -9 gazebo ; killall -9 gzserver  ; killall -9 gzclient ; killall -9 rosmaster ; killall -9 rviz ; rosnode kill -a ; killall -9 xterm

echo "Robert Simulation Closed."

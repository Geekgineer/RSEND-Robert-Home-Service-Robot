cmake_minimum_required(VERSION 2.8.3)
project(robert_pick_objects)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  move_base_msgs
  actionlib
  tf
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES robert_pick_objects
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(robert_pick_objects src/robert_pick_objects.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(robert_pick_objects ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(robert_pick_objects
   ${catkin_LIBRARIES}
 )

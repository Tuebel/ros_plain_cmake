############################################################################
# Minimal example of a catkin package that consumes the plain_cmake package.
# Build it in the workspace using catkin build or catkin_make_isolated.
############################################################################

cmake_minimum_required(VERSION 3.0.2)
project(catkin_pkg_2)

# Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# Find catkin macros and libraries
# if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
# is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS catkin_pkg roscpp std_msgs)

message("catkin libs: ${catkin_LIBRARIES}")

# call catkin_package
catkin_package(
 CATKIN_DEPENDS catkin_pkg roscpp std_msgs)

###########
## Build ##
###########

# declare the executable node
add_executable(test_node src/test_node.cpp)
# add include directories
target_include_directories(test_node 
  PRIVATE ${catkin_INCLUDE_DIRS})
# link with the plain_cmake_lib
target_link_libraries(test_node
  PRIVATE ${catkin_LIBRARIES})

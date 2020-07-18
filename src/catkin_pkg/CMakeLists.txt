############################################################################
# Minimal example of a catkin package that consumes the plain_cmake package.
# Build it in the workspace using catkin build or catkin_make_isolated.
############################################################################

cmake_minimum_required(VERSION 3.0.2)
project(catkin_pkg)

# Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

# Find catkin macros and libraries
# if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
# is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

# System dependencies are found with CMake's conventions
find_package(plain_cmake REQUIRED)

# call catkin_package
catkin_package(
 CATKIN_DEPENDS roscpp std_msgs
 DEPENDS plain_cmake
)

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
  PRIVATE ${catkin_LIBRARIES} plain_cmake_lib)

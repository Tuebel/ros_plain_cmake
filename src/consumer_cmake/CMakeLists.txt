
###########################################################################
# Minimal example of a CMake package that consumes the plain_cmake package.
# The plain_cmake package must have been built and checkinstalled.
###########################################################################

#######################
# general configruation
#######################
cmake_minimum_required(VERSION 3.0)
project(consumer)
set(CMAKE_CXX_STANDARD 11)
set(CONSUMER_VERSION 0.1)

# Output more warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

##############
# dependencies
##############

find_package(plain_cmake)

###################
# target defintions
###################

add_executable(app src/app.cpp)
target_link_libraries(app plain_cmake_lib)

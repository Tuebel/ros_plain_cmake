cmake_minimum_required(VERSION 2.8.3)
project(plain_cmake)
set(CMAKE_CXX_STANDARD 11)
set(PLAIN_CMAKE_VERSION 0.1)
# TODO required?
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Output more warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# System dependencies
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Declare a C++ library
add_library(plain_cmake_lib
  src/matrix_operations.cpp)
target_include_directories(plain_cmake_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include)
target_link_libraries(plain_cmake_lib PUBLIC
  Eigen3::Eigen)

# Declare an executable
add_executable(example
  src/example.cpp)
target_link_libraries(example
  plain_cmake_lib)

# install
# TODO install public headers?
install(TARGETS plain_cmake_lib example
  EXPORT plain_cmakeTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/plain_cmake)
install(DIRECTORY include DESTINATION include)
  
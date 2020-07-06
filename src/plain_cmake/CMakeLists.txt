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
add_library(plain_cmake_lib src/matrix_operations.cpp)
# different locations on build and after install
target_include_directories(plain_cmake_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(plain_cmake_lib PUBLIC Eigen3::Eigen)

# Declare an executable
add_executable(example src/example.cpp)
target_link_libraries(example plain_cmake_lib)

# install targets: libraries and binaries
install(TARGETS plain_cmake_lib example
  EXPORT plain_cmakeTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
# install header files, either set PUBLIC_HEADERS or copy include dir
# TODO update scigl_render
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
)

# Generate CMake package
# https://cmake.org/cmake/help/v3.18/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfigVersion.cmake
  VERSION ${PLAIN_CMAKE_VERSION}
  COMPATIBILITY SameMajorVersion)

export(EXPORT plain_cmakeTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeTargets.cmake
  NAMESPACE plain_cmake::)

set(ConfigPackageLocation ${CMAKE_INSTALL_DATAROOTDIR}/plain_cmake/cmake)
configure_package_config_file(
  plain_cmakeConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfig.cmake
  INSTALL_DESTINATION ${ConfigPackageLocation}
  PATH_VARS plain_cmake_INCLUDE_DIRS)

install(EXPORT plain_cmakeTargets
  FILE
    plain_cmakeTargets.cmake
  NAMESPACE
    plain_cmake::
  DESTINATION
    ${ConfigPackageLocation})
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfigVersion.cmake
  DESTINATION
    ${ConfigPackageLocation})



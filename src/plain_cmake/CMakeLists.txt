#######################
# general configruation
#######################
cmake_minimum_required(VERSION 3.0)
project(plain_cmake)
set(CMAKE_CXX_STANDARD 11)
set(PLAIN_CMAKE_VERSION 0.1)

# Output more warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# provides default CMAKE_INSTALL_<dir> variables
include(GNUInstallDirs)
# helpers to generate <package>Config.cmake
# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)

# where to install the cmake files
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/plain_cmake/cmake)

##############
# dependencies
##############
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

###################
# target defintions
###################

# declare library
add_library(plain_cmake_lib src/matrix_operations.cpp)
# different locations on build and after install
target_include_directories(plain_cmake_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(plain_cmake_lib PUBLIC Eigen3::Eigen)

# declare an executable
add_executable(example_app src/example_app.cpp)
target_link_libraries(example_app plain_cmake_lib)

#################
# install targets
#################

# libs and binaries, generate export targets
install(TARGETS plain_cmake_lib example_app
  EXPORT plain_cmakeTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
# header files, not the "/" after include
install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

################
# export targets
################

# for build tree / in workspace
export(EXPORT plain_cmakeTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeTargets.cmake
  NAMESPACE plain_cmake::)

# for installation
install(EXPORT plain_cmakeTargets
  FILE plain_cmakeTargets.cmake
  NAMESPACE plain_cmake::
  DESTINATION ${ConfigPackageLocation})

###########################
# CMake package generation
###########################

# generate package version file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfigVersion.cmake
  VERSION ${PLAIN_CMAKE_VERSION}
  COMPATIBILITY SameMajorVersion)

# generate package configuration file
set(plain_cmake_INCLUDE_DIRS include)
configure_package_config_file(
  plain_cmakeConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfig.cmake
  INSTALL_DESTINATION ${ConfigPackageLocation}
  PATH_VARS plain_cmake_INCLUDE_DIRS)

# install the package configuration files
install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/plain_cmakeConfigVersion.cmake
  DESTINATION ${ConfigPackageLocation})
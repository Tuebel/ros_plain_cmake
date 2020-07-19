#######################
# general configruation
#######################
cmake_minimum_required(VERSION 3.0)
project(plain_cmake)
set(PLAIN_CMAKE_VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)

# Output more warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#######################
# include CMake helpers
#######################

# provides default CMAKE_INSTALL_<dir> variables
include(GNUInstallDirs)
# helpers to generate <package>Config.cmake
include(CMakePackageConfigHelpers)

##############
# dependencies
##############
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

###################
# target defintions
###################

# declare library
add_library(${CMAKE_PROJECT_NAME}_lib src/matrix_operations.cpp)
# different locations on build and after install
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(${CMAKE_PROJECT_NAME}_lib PUBLIC Eigen3::Eigen)

# declare an executable
add_executable(example_app src/example_app.cpp)
target_link_libraries(example_app ${CMAKE_PROJECT_NAME}_lib)

#################
# install targets
#################

# install location of generated cmake config files
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}/cmake)

# libs and binaries, generate export targets
install(TARGETS ${CMAKE_PROJECT_NAME}_lib example_app
  EXPORT ${CMAKE_PROJECT_NAME}Targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
# header files, note the "/" after include
install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")

################
# export targets
################

# for build tree / in workspace
export(EXPORT ${CMAKE_PROJECT_NAME}Targets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake
  NAMESPACE ${CMAKE_PROJECT_NAME}::)

# for installation
install(EXPORT ${CMAKE_PROJECT_NAME}Targets
  FILE ${CMAKE_PROJECT_NAME}Targets.cmake
  NAMESPACE ${CMAKE_PROJECT_NAME}::
  DESTINATION ${ConfigPackageLocation})

###########################
# CMake package generation
###########################

# generate package version file
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PLAIN_CMAKE_VERSION}
  COMPATIBILITY SameMajorVersion)

# generate package configuration file
set(${CMAKE_PROJECT_NAME}_INCLUDE_DIRS include)
configure_package_config_file(
  ${CMAKE_PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${ConfigPackageLocation}
  PATH_VARS ${CMAKE_PROJECT_NAME}_INCLUDE_DIRS)

# install the package configuration files
install(FILES 
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${ConfigPackageLocation})
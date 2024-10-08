cmake_minimum_required(VERSION 3.0.2)
project(sbgc32_ros_driver)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED
  roscpp)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES sbgc32_ros_driver
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
set(PATH_TO_SOURCES sbgc32-serial-api/sources)
set(PATH_TO_DRIVERS sbgc32-serial-api/drivers/LinuxDriver)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

set(CMAKE_BUILD_TYPE Debug)
if(NOT SBGC_SERIAL_PORT)
  set(SBGC_SERIAL_PORT "/dev/ttyUSBsbgc")
endif()
add_library(sbgc32_wrapper STATIC
        ${PATH_TO_DRIVERS}/driver_Linux.c
        ${PATH_TO_DRIVERS}/driver_Linux.h
        ${PATH_TO_SOURCES}/adjvar/adjvar.c
        ${PATH_TO_SOURCES}/adjvar/adjvar.h
        ${PATH_TO_SOURCES}/calib/calib.c
        ${PATH_TO_SOURCES}/calib/calib.h
        ${PATH_TO_SOURCES}/core/core.c
        ${PATH_TO_SOURCES}/core/core.h
        ${PATH_TO_SOURCES}/eeprom/eeprom.c
        ${PATH_TO_SOURCES}/eeprom/eeprom.h
        ${PATH_TO_SOURCES}/gimbalControl/gimbalControl.c
        ${PATH_TO_SOURCES}/gimbalControl/gimbalControl.h
        ${PATH_TO_SOURCES}/imu/imu.c
        ${PATH_TO_SOURCES}/imu/imu.h
        ${PATH_TO_SOURCES}/profiles/profiles.c
        ${PATH_TO_SOURCES}/profiles/profiles.h
        ${PATH_TO_SOURCES}/realtime/realtime.c
        ${PATH_TO_SOURCES}/realtime/realtime.h
        ${PATH_TO_SOURCES}/service/service.c
        ${PATH_TO_SOURCES}/service/service.h
        src/sbgc32_wrapper.cpp)
target_include_directories(sbgc32_wrapper PRIVATE ${PATH_TO_DRIVERS})
target_include_directories(sbgc32_wrapper PRIVATE ${PATH_TO_SOURCES})
set_property(TARGET sbgc32_wrapper PROPERTY CXX_STANDARD 11)
target_compile_definitions(sbgc32_wrapper PRIVATE "SBGC_SERIAL_PORT=\"${SBGC_SERIAL_PORT}\"")

add_executable(sbgc32_node src/sbgc32_node.cpp)
target_link_libraries(sbgc32_node sbgc32_wrapper ${catkin_LIBRARIES})

## Declare a C++ library
# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/sbgc32_ros_driver.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/sbgc32_ros_driver_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# Mark executables and/or libraries for installation
install(
  TARGETS sbgc32_wrapper sbgc32_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# Mark cpp header files for installation
install(DIRECTORY include/${PROJECT_NAME}/ DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

# Mark launch folder for installation
# install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# Mark config folder for installation
# install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

# Mark all the *.xml files for installation
install(FILES package.xml
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_sbgc32_ros_driver.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)

# Unset cache so we can go back to using the default value
unset(SBGC_SERIAL_PORT CACHE)

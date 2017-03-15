cmake_minimum_required(VERSION 2.8.12)
project(com2gui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(YARP REQUIRED)
  
include_directories(${YARP_INCLUDE_DIRS})
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpInstallationHelpers)

add_executable(com2gui main.cpp)

target_link_libraries(com2gui ${YARP_LIBRARIES})

install(TARGETS com2gui DESTINATION bin)



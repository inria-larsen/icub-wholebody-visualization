cmake_minimum_required(VERSION 2.8.12)
project(torqueviewer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(YARP REQUIRED)
  
include_directories(${YARP_INCLUDE_DIRS})

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
include(YarpInstallationHelpers)

qt5_wrap_ui(UI_HEADERS dialog.ui)
qt5_add_resources(UI_RESOURCES images.qrc)

add_executable(torqueviewer main.cpp dialog.cpp torqueview.cpp torquegetter.cpp torqueitem.cpp ${UI_HEADERS} ${UI_RESOURCES} )

target_link_libraries(torqueviewer Qt5::Widgets Qt5::Core ${YARP_LIBRARIES})
configure_file(torqueviewer.ini torqueviewer.ini COPYONLY)

install (TARGETS torqueviewer DESTINATION bin)

# where to install ? config_data_dir does not work (not found by RF later on) so
# we rely for now on the default data_dir - need to setup a context instead (TODO)
yarp_install(FILES torqueviewer.ini DESTINATION ${YARP_DATA_INSTALL_DIR})

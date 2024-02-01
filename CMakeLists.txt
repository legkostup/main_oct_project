cmake_minimum_required(VERSION 3.7...3.21)
project(main_oct_project VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "~~~~~ Cmake run ~~~~~")
message(STATUS "System name: '${CMAKE_SYSTEM_NAME}'")

# -----  wxWidgets  -----
#   SET(wxWidgets_ROOT_DIR <wxWidgets Directory>)  # to change the default root dir to wxWidgets
#   SET(wxWidgets_CONFIGURATION mswud)  # to find appropriate configurations
#   FIND_PACKAGE(wxWidgets COMPONENTS core base REQUIRED)  # to find package dir calling for example /usr/share/cmake-3.10/Modules/FindwxWidgets.cmake
#   INCLUDE(${wxWidgets_USE_FILE})  # to include wxWidgets files to this project
#   TARGET_LINK_LIBRARIES(<YourTarget> ${wxWidgets_LIBRARIES})  # to add (link) wxWidgets lib to this executable project

find_package(wxWidgets CONFIG REQUIRED)
if (NOT wxWidgets_FOUND)
    message(ERROR "~~~~~ Compilation error! Package wxWidgets not found! ~~~~~")
endif ()



#include(CTest)
#enable_testing()
add_executable(main_oct_project main.cpp)


target_link_libraries(main_oct_project
    PRIVATE wx::core wx::base)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)



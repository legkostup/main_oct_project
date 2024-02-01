cmake_minimum_required(VERSION 3.7...3.21)
project(main_oct_project VERSION 0.1.0 LANGUAGES C CXX)

#include(CTest)
#enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# paths for output bin:
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# paths for shared libs:
    # LIBRARY_OUTPUT_PATH
    # CMAKE_LIBRARY_OUTPUT_DIRECTORY

# paths for static libs:
    # CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    # ARCHIVE_OUTPUT_PATH

# CMAKE_BINARY_DIR : Full path to top level of build tree and binary output folder, by default it is defined as top level of build tree.
# CMAKE_HOME_DIRECTORY : Path to top of source tree
# CMAKE_SOURCE_DIR : Full path to top level of source tree.
# CMAKE_INCLUDE_PATH : Path used to find file, path

# -----  TOOLCHAIN  -----
# if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#   if(DEFINED ENV{VITASDK})
#     set(CMAKE_TOOLCHAIN_FILE "/home/victor/dev/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "toolchain file")
#   else()
#     message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
#   endif()
# endif()


message(STATUS "~~~~~ Cmake run ~~~~~")
# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    message("This is a Windows System")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Linux)
    message("This is a Linux System")
else()
    message("This is unknown system")
endif()




# -----  OpenMP  -----
if(NOT TARGET OpenMP::OpenMP_CXX)
    find_package(Threads REQUIRED)
    add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
    set_property(TARGET OpenMP::OpenMP_CXX
                 PROPERTY INTERFACE_COMPILE_OPTIONS ${OpenMP_CXX_FLAGS})
    # Only works if the same flag is passed to the linker; use CMake 3.9+ otherwise (Intel, AppleClang)
    set_property(TARGET OpenMP::OpenMP_CXX
                 PROPERTY INTERFACE_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} Threads::Threads)
endif()


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

# -----  Boost  -----
# if(NOT Boost_FOUND)
#     message(ERROR " Boost Found")
#     include_directories(${Boost_INCLUDE_DIRS})
#     target_link_libraries(cmake_hello ${Boost_LIBRARIES})
# endif()

find_package(Armadillo CONFIG REQUIRED)
find_package(ensmallen CONFIG REQUIRED)


set(SOURCES
    scr/main.cpp 
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/../lib)
message(${CMAKE_BINARY_DIR})
add_library(algo SHARED scr/algo.cpp)
#add_library(math STATIC lib/math/operations.cpp)

add_executable(main_oct_project ${SOURCES})

target_link_libraries(main_oct_project PRIVATE algo)

target_link_libraries(main_oct_project PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(main_oct_project PRIVATE armadillo)
target_link_libraries(main_oct_project PRIVATE wx::core wx::base)
target_link_libraries(main_oct_project PRIVATE ensmallen::ensmallen)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)



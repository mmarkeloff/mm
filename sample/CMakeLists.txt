cmake_minimum_required(VERSION 3.6)

project(mm-sample)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(../cmake/DownloadProject.cmake)

download_project(
    PROJ cpp-crtp-singleton
    GIT_REPOSITORY https://github.com/mmarkeloff/cpp-crtp-singleton.git
    GIT_TAG main
    ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

include_directories(../include/mm)
include_directories(../src)
include_directories(${cpp-crtp-singleton_SOURCE_DIR}/include/cpp-crtp-singleton)

add_library(mm-sample-some-mod SHARED some_mod.cpp)
add_library(mm-sample-another-mod SHARED another_mod.cpp)

add_executable(mm-sample-main main.cpp)
cmake_minimum_required(VERSION 3.31.3)
project(test)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

set(SOURCE_FILES control.cpp)
add_executable(compute compute.cpp)
add_executable(test ${SOURCE_FILES} BinarySearchTree.cpp)

target_include_directories(test PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_include_directories(compute PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(test PUBLIC ${ZeroMQ_LIBRARY})
target_link_libraries(compute PUBLIC ${ZeroMQ_LIBRARY})



cmake_minimum_required(VERSION 3.1)

project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp mqtt.cpp)

find_package(Threads REQUIRED)
target_link_libraries(main Threads::Threads)

find_library(MOSQUITTO_LIB mosquittopp)
target_link_libraries(main ${MOSQUITTO_LIB})

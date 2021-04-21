cmake_minimum_required(VERSION 3.15)
project(network.ars-test)

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(NOT DEFINED GWE_ROOT_DIRECTORY)
    set(GWE_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)
endif()

include_directories(include)
include_directories(${GWE_ROOT_DIRECTORY}/network.ars/include)

unset(SOURCES)
set(SOURCES  src/pch.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} network.ars)
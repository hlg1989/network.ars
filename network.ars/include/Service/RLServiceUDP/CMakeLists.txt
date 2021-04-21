project(RLServiceUDP)
cmake_minimum_required(VERSION 2.4)
set(CMAKE_CXX_STANDARD 11)

message(STATUS "compiling dir :${CMAKE_CURRENT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../../..)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

aux_source_directory(${CMAKE_CURRENT_BINARY_DIR}/../../.. SRCS)
aux_source_directory(${CMAKE_CURRENT_BINARY_DIR} SRCS)

add_library(${PROJECT_NAME} SHARED ${SRCS})
install(TARGETS ${PROJECT_NAME} DESTINATION lib)


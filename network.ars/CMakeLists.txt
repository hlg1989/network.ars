cmake_minimum_required(VERSION 3.15)
project(network.ars VERSION 0.1.0)

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(NOT DEFINED GWE_ROOT_DIRECTORY)
    set(GWE_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif()

include_directories(include)

unset(SOURCES)
aux_source_directory(src SOURCES)
aux_source_directory(src/Service SOURCES)
aux_source_directory(src/Service/RLServiceJanus SOURCES)
aux_source_directory(src/Service/RLServiceUDP SROUCES)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

find_package(Boost COMPONENTS system filesystem thread regex date_time chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
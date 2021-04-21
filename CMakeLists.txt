cmake_minimum_required(VERSION 3.15)
project(network.ars VERSION 0.1.0)

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(NOT DEFINED GWE_ROOT_DIRECTORY)
    set(GWE_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(NOT DEFINED TARGET_CPU)
    set(TARGET_CPU "x64")
endif()

set(GWE_PREBUILTS_ROOT_DIRECTORY /usr/local/gshare/${TARGET_CPU})

if( TARGET_CPU STREQUAL "x86" )
    message( STATUS "32-bit build" )
else()
    message( STATUS "64-bit build" )
endif()


list(APPEND CMAKE_FIND_ROOT_PATH "${GWE_PREBUILTS_ROOT_DIRECTORY}")
message( STATUS "CMAKE_FIND_ROOT_PATH: ${CMAKE_FIND_ROOT_PATH}" )

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    add_subdirectory(network.ars)
    add_subdirectory(tests)
else()
    add_subdirectory(network.ars)
endif()



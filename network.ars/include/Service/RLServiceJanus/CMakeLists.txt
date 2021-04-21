project(RLServiceJanus)
cmake_minimum_required(VERSION 2.4)
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(RL_SERVICE_JANUS_SRC RLServiceJanusCInterface.h RLServiceJanusCInterface.cpp)
aux_source_directory(${CMAKE_CURRENT_BINARY_DIR}/../RLServiceUDP RL_SERVICE_UDP_SRC)
aux_source_directory(${CMAKE_CURRENT_BINARY_DIR}/../.. RL_SRC)

set(ALL_SRCS ${RL_SERVICE_UDP_SRC} ${RL_SRC} ${RL_SERVICE_JANUS_SRC})

add_library(${PROJECT_NAME} SHARED ${ALL_SRCS} )
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ./RLServiceJanusCInterface.h DESTINATION include)

#add_library(RLClientTCP SHARED RLClientTCPbase.h RLClientTCPDelegate.h RLClientTCPNet.hpp RLClientTCPStateManager.hpp)

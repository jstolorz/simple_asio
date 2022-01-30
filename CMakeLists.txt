cmake_minimum_required(VERSION 3.21)
project(simple_asio)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(manage_memory)
add_subdirectory(asio_buffer)
add_subdirectory(./multicast/sender)
add_subdirectory(./multicast/receiver)
add_subdirectory(theboostcpplibraries)
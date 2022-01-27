cmake_minimum_required(VERSION 3.21)
project(manage_memory)

set(CMAKE_CXX_STANDARD 20)

include_directories("C:/SDK/lib/asio-1.20.0/asio-1.20.0/include")

add_executable(${PROJECT_NAME} main.cpp ../asio_buffer/main.cpp ../uidaemon_client/uidaemon_client.h)

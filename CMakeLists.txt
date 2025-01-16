cmake_minimum_required(VERSION 3.30)
project(Echo_Server_C C)

set(CMAKE_C_STANDARD 23)

add_executable(Echo_Server_C main-server.c)
add_executable(Echo_Client_C main-client.c)

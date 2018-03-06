cmake_minimum_required(VERSION 3.9)
project(single_machine_RPQ)

set(CMAKE_CXX_STANDARD 11)

add_executable(single_machine_RPQ main.cpp machine.cpp machine.h)
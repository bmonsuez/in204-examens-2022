cmake_minimum_required(VERSION 3.0.0)

project(annexes VERSION 0.1.0)

add_executable(annexes view.cpp)

set_property(TARGET annexes PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET annexes PROPERTY CXX_STANDARD 20)

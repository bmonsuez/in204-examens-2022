cmake_minimum_required(VERSION 3.0.0)

project(part4 VERSION 0.1.0)

add_executable(part4 view.cpp)

set_property(TARGET part4 PROPERTY CXX_STANDARD_REQUIRED TRUE)
set_property(TARGET part4 PROPERTY CXX_STANDARD 20)

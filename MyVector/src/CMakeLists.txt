cmake_minimum_required(VERSION 3.5)
set (VERSION 0.1)
set (PACKAGE MyVector)
project (${PACKAGE})

add_executable (tester tester.cpp MyVector.cpp)
add_library(MyVector INTERFACE ../include/MyVector.h)
include_directories (../include)


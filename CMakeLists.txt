cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
set(PACKAGE Book)


project(${PACKAGE})

include_directories(include)

add_library(time INTERFACE include/Date.h include/Year.h)

##accede alla subdirectory src
add_subdirectory(src)



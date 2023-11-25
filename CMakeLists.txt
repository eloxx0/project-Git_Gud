cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(PACKAGE Date)

##creo il progetto
project(${PACKAGE})

include_directories(include)

##accede al CMakeLists.txt nella subdirectory include
add_subdirectory(include)

##accede al CMakeLists.txt nella subdirectory src
add_subdirectory(src)



cmake_minimum_required(VERSION 3.5) 
set(CMAKE_CXX_STANDARD 11)
set(PACKAGE Git_Gud)

##creo il progetto
project(${PACKAGE} VERSION 1.0)

include_directories(include)

##accede al CMakeLists.txt nella subdirectory include
add_subdirectory(include)

##accede al CMakeLists.txt nella subdirectory src
add_subdirectory(src)



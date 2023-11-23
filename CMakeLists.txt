cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(PACKAGE Date)
set(PROJECT_BINARY_DIR bin)

##creo il progetto
project(${PACKAGE})

include_directories(include)

add_subdirectory(include)
##accede alla subdirectory src
add_subdirectory(src)



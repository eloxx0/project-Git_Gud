cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
set(PACKAGE Date)
set(PROJECT_BINARY_DIR bin)

##creo il progetto
project(${PACKAGE})

include_directories(include)

##INTERFACE crea una interfaccia. Non viene compilata e non viene incluso come
##un target nel buildsystem
add_library(time INTERFACE include/Date.h include/Year.h)

##accede alla subdirectory src
add_subdirectory(src)



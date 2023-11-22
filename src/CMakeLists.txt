##SHARED crea una libreria dinamica
add_library(${PACKAGE} SHARED Date.cpp Year.cpp)

add_executable(main main.cpp)


target_link_libraries(main ${PACKAGE})


##SHARED crea una libreria dinamica
add_library(${PACKAGE} SHARED Date.cpp Year.cpp)

add_executable(main main.cpp)

install(TARGETS main DESTINATION ../bin)

target_link_libraries(main ${PACKAGE})


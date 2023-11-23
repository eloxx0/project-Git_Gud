##SHARED crea una libreria dinamica condivisa
add_library(${PACKAGE} SHARED Date.cpp Year.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
##target per la creazione di un eseguibile
add_executable(main main.cpp)

add_custom_command(TARGET main POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} main
    COMMENT "Created ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main")

##install(TARGETS main DESTINATION ../bin)

##indica quali librerie utilizzare quando linka un determinato target (libreria o eseguibile)
target_link_libraries(main ${PACKAGE})


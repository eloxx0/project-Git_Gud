##SHARED crea una libreria dinamica condivisa
add_library(${PACKAGE} SHARED Date.cpp Year.cpp Book.cpp Bookshelf.cpp Isbn.cpp)

##imposto come directory di runtime la cartella bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

##target per la creazione di un eseguibile
add_executable(main main.cpp)

##sposta l'eseguibile nella cartella bin
##${CMAKE_COMMAND} variabile che contiene il comando: cmake
##COMMAND esegue comandi bash
add_custom_command(TARGET main POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} main
    COMMENT "Created ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main")
##La cartella main dopo il move è vuota, questo comando la cancella
file(REMOVE_RECURSE main)

##indica quali librerie utilizzare quando linka un determinato target (libreria o eseguibile)
##necessario per permettere all'eseguibile di essere linkato alle librerie dinamiche
target_link_libraries(main ${PACKAGE})


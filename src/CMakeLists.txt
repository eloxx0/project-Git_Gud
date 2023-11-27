##SHARED crea una libreria dinamica condivisa
add_library(${PACKAGE} SHARED Date.cpp Year.cpp Book.cpp Bookshelf.cpp Isbn.cpp)

##imposto come directory di runtime la cartella bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

##target per la creazione di un eseguibile
add_executable(main main.cpp)

##indica quali librerie utilizzare quando linka un determinato target (libreria o eseguibile)
##necessario per permettere all'eseguibile di essere linkato alle librerie dinamiche
target_link_libraries(main ${PACKAGE})


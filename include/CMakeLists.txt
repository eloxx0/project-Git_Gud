##INTERFACE crea una interfaccia. Non viene compilata e non viene incluso come
##un target nel buildsystem
add_library(time INTERFACE Date.h Year.h)

add_library(Book INTERFACE Book.h Bookshelf.h Isbn.h)


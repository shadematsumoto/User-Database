project_debug: llist_debug.o user_interface_debug.o
        g++ -o project_debug llist_debug.o user_interface_debug.o

llist_debug.o: llist.cpp llist.h record.h
        g++ -ansi -pedantic-errors -Wall -DDEBUGMODE -c llist.cpp -o llist_debug.o

user_interface_debug.o: user_interface.cpp llist.h record.h
        g++ -ansi -pedantic-errors -Wall -DDEBUGMODE -c user_interface.cpp -o user_interface_debug.o

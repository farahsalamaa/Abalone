CC=gcc
CPPFLAGS= -DDEBUG 
CFLAGS = `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0` -pthread
EXEC=abalone

all: clean test $(EXEC)

# ./etat.o ./mouvement.o
$(EXEC): ./main.o ./abalone_terminal.o ./abalone_gtk.o  ./serveur.o ./client.o  ./ia.o ./mouvement.o ./abalone_threads.o
	$(CC) -o $@ $^ $(LDFLAGS) 

test: ./main_test.o ./mouvement_test.o ./abalone_terminal.o ./serveur.o ./client.o ./mouvement.o ./ia.o
	$(CC) -fprofile-arcs -ftest-coverage -o $@ $(addsuffix _t, $^) $(LDFLAGS) 
	./$@

coverage: test
	gcov -pb mouvement.c

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $< 
	$(CC) -fprofile-arcs -ftest-coverage -c $(CPPFLAGS) $(CFLAGS) -o $@_t $<

# Dependances
./main.o: ./main.c ./abalone_terminal.h ./abalone_gtk.h ./serveur.h ./client.h ./mouvement.h ./ia.h ./abalone_threads.h
./abalone_terminal.o :./abalone_terminal.c  ./abalone_gtk.h ./serveur.h ./client.h ./mouvement.h ./ia.h
./abalone_gtk.o:./abalone_gtk.c ./abalone_terminal.h  ./serveur.h ./client.h ./mouvement.h ./ia.h
./mouvement.o :./mouvement.c ./abalone_terminal.h ./abalone_gtk.h ./serveur.h ./client.h ./ia.h
./ia.o:./ia.c ./abalone_terminal.h ./abalone_gtk.h ./serveur.h ./client.h ./mouvement.h 
./serveur.o:./serveur.c ./abalone_terminal.h ./abalone_gtk.h ./serveur.h ./client.h ./mouvement.h ./ia.h
./client.o:./client.c ./abalone_terminal.h ./abalone_gtk.h ./serveur.h ./mouvement.h ./ia.h
./abalone_threads.o: ./abalone_threads.c ./abalone_threads.h ./abalone_terminal.h ./mouvement.h

./main_test.o: ./main_test.c ./mouvement_test.h
./mouvement_test.o: ./abalone_terminal.h ./serveur.h ./client.h ./mouvement.h ./ia.h

.PHONY: clean docs

docs:
	doxygen Doxyfile

clean:
	-rm $(EXEC)
	-rm test
	-rm *.o
	-rm *.o_t
	-rm *.gcno
	-rm *.gcda
	-rm *.gcov

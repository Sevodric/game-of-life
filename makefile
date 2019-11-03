sgdir = lib/sg/
goldir = lib/gol/
CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -I$(sgdir) -I$(goldir)
LDFLAGS = -lX11 -lm
objects = main.o $(goldir)gol.o $(sgdir)sg.o $(goldir)ic.o
executable = main

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c $(sgdir)sg.h $(goldir)gol.h $(goldir)ic.h
sg.o: $(sgdir)sg.c $(sgdir)sg.h
gol.o: $(goldir)gol.c $(sgdir)sg.h $(goldir)gol.h
ic.o: $(icdir)ic.c $(goldir)gol.h $(icdir)ic.h

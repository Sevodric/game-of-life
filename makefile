sgdir = lib/sg/
goldir = lib/gol/
CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2
LDFLAGS = -lX11 -lm
VPATH = $(sgdir) $(goldir)
objects = main.o $(goldir)gol.o $(sgdir)sg.o
executable = main

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c
$(goldir)gol.o: $(goldir)gol.c $(goldir)gol.h
$(sgdir)sg.o: $(sgdir)sg.c $(sgdir)sg.h

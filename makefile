CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic                \
	 -Wwrite-strings -O2 -Iinclude/ -g
LDFLAGS = -lX11
objects = main.o src/gol.o src/sg.o
executable = main

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c include/sg.h include/gol.h
sg.o: src/sg.c include/sg.h
gol.o: src/gol.c include/sg.h include/gol.h

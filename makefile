CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lX11
objects = main.o sg.o
executable = main

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c sg.h
sg.o: sg.c sg.h

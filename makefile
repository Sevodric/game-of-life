CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lX11
objects = gol.o sg.o
executable = gol

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

gol.o: gol.c sg.h
sg.o: sg.c sg.h

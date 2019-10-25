sgdir = sg/
CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -D_POSIX_C_SOURCE=200809L -I$(sgdir)
LDFLAGS = -lX11 -lm
VPATH=$(sgdir)
objects = main.o gol.o $(sgdir)sg.o
executable = main

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c sg.h gol.h
gol.o: gol.c gol.h
$(sgdir)sg.o: sg.c sg.h

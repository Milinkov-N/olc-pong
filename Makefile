CC=gcc
CFLAGS=-Wall -Wextra -Werror
EXE=./bin/pong.exe

all: pong

pong:
	$(CC) $(CFLAGS) main.c -o $(EXE)

rebuild: clean all

clean:
	rm $(EXE)
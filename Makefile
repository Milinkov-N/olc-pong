CC=gcc
CFLAGS=-Wall -Wextra -Werror
EXE=bin/pong.exe

pong:
	$(CC) $(CFLAGS) main.c -o $(EXE)

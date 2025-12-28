# Makefile for Asteroids Game
# Gabriel Marques

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lX11 -lm

# Source files
SRCS = Game.c Gamefunc.c
OBJS = Game.o Gamefunc.o gfx2.o

# Executable 
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

Game.o: Game.c Gamefunc.h gfx2.h
	$(CC) $(CFLAGS) -c Game.c

Gamefunc.o: Gamefunc.c Gamefunc.h gfx2.h
	$(CC) $(CFLAGS) -c Gamefunc.c

clean:
	rm -f Game.o Gamefunc.o $(TARGET)

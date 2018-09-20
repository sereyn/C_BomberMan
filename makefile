CC=gcc
FLAGS=-W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
POSTFLAGS=`pkg-config --libs-only-l MLV`

all: main

start: main
	./$<

main: main.c
	$(CC) $(FLAGS) $< $(POSTFLAGS) -o $@


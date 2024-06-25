CFLAGS = -fdiagnostics-color=always -g -std=c99 -pedantic -Wall -Werror -Wvla

all: main

main: main.o graph.o heap.o adj_matrix.o
	gcc main.o graph.o heap.o adj_matrix.o -lm -g -o main

main.o: main.c heap.h adj_matrix.h
	gcc $(CFLAGS) -c main.c -lm

graph.o: graph.c graph.h includes.h
	gcc $(CFLAGS) -c graph.c -lm

heap.o: heap.c heap.h graph.h
	gcc $(CFLAGS) -c heap.c -lm

adj_matrix.o: adj_matrix.c adj_matrix.h graph.h
	gcc $(CFLAGS) -c adj_matrix.c -lm
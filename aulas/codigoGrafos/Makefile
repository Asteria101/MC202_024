LIB=.
INCLUDE=.
BIN=.
SRC=.
OBJ=.
FLAGS= -O3 -Wall  -fPIC -fopenmp -pthread -std=gnu99 -pedantic 

INCLUDES=-I$(INCLUDE)

all: libmc202 	
	@echo
	@echo "libmc202.a built..."
	@echo "DONE."

libmc202: $(LIB)/libmc202.a

$(LIB)/libmc202.a: \
$(OBJ)/Fila.o \
$(OBJ)/Pilha.o \
$(OBJ)/Heap.o \
$(OBJ)/Grafo.o 
	ar csr $(LIB)/libmc202.a \
$(OBJ)/Fila.o \
$(OBJ)/Pilha.o \
$(OBJ)/Heap.o \
$(OBJ)/Grafo.o 

$(OBJ)/Fila.o: $(INCLUDE)/Fila.h $(SRC)/Fila.c
	gcc $(FLAGS) -c $(SRC)/Fila.c $(INCLUDES) -o $(OBJ)/Fila.o

$(OBJ)/Pilha.o: $(INCLUDE)/Pilha.h $(SRC)/Pilha.c
	gcc $(FLAGS) -c $(SRC)/Pilha.c $(INCLUDES) -o $(OBJ)/Pilha.o

$(OBJ)/Heap.o: $(INCLUDE)/Heap.h $(SRC)/Heap.c
	gcc $(FLAGS) -c $(SRC)/Heap.c $(INCLUDES) -o $(OBJ)/Heap.o

$(OBJ)/Grafo.o: $(INCLUDE)/Grafo.h $(SRC)/Grafo.c
	gcc $(FLAGS) -c $(SRC)/Grafo.c $(INCLUDES) -o $(OBJ)/Grafo.o

TestGrafo: libmc202 
	make
	gcc $(FLAGS) TestGrafo.c -o TestGrafo -L$(LIB) -lmc202 -lm


clean:
	rm -f $(LIB)/libmc202.a; rm -f $(OBJ)/*.o; rm -f TestGrafo

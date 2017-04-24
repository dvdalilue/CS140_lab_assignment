
CC = g++
CFLAGS = -g -Wall
BIN = BST1 BST2 BST3

all: $(BIN)

BST1: BST1.h BST_usage1.cpp
	$(CC) $(CFLAGS) -o BST1 BST_usage1.cpp

BST2: BST2.h BST_usage2.cpp
	$(CC) $(CFLAGS) -o BST2 BST_usage2.cpp

BST3: BST3.h BST_usage3.cpp
	$(CC) $(CFLAGS) -o BST3 BST_usage3.cpp

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	rm -f $(BIN) *.o

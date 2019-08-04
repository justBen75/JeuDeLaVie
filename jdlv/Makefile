CC=gcc 
CFLAGS=-W -Wall -ansi -g -pedantic -I $(HOME)/include/
LDFLAGS=-L $(HOME)/lib/ -lgraphics -lX11
EXEC=./bin/jeu
SRC= $(wildcard ./src/*.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

./bin/jeu: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
jeu.o : jeu.c
	$(CC) -o $@ -c $< $(CFLAGS)
.PHONY: clean mrproper

clean:
	rm -rf src/*.o

mrproper: clean
	rm -rf $(EXEC) 


